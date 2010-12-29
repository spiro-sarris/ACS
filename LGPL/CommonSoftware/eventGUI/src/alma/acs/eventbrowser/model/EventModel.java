package alma.acs.eventbrowser.model;

import gov.sandia.CosNotification.NotificationServiceMonitorControl;
import gov.sandia.CosNotification.NotificationServiceMonitorControlHelper;
import gov.sandia.CosNotification.NotificationServiceMonitorControlPackage.InvalidName;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.logging.Logger;

import org.eclipse.core.runtime.IStatus;
import org.eclipse.core.runtime.Platform;
import org.eclipse.core.runtime.Status;
import org.eclipse.jface.dialogs.MessageDialog;
import org.eclipse.ui.PlatformUI;
import org.omg.CORBA.ORB;
import org.omg.CosNaming.Binding;
import org.omg.CosNaming.BindingIteratorHolder;
import org.omg.CosNaming.BindingListHolder;
import org.omg.CosNaming.NameComponent;
import org.omg.CosNaming.NamingContext;
import org.omg.CosNaming.NamingContextPackage.CannotProceed;
import org.omg.CosNaming.NamingContextPackage.NotFound;
import org.omg.CosNotifyChannelAdmin.ChannelNotFound;
import org.omg.CosNotifyChannelAdmin.EventChannel;
import org.omg.CosNotifyChannelAdmin.EventChannelFactory;
import org.omg.CosNotifyChannelAdmin.EventChannelFactoryHelper;
import org.omg.CosNotifyChannelAdmin.EventChannelHelper;
import org.omg.DynamicAny.DynAnyFactory;
import org.omg.DynamicAny.DynAnyFactoryHelper;

import Monitor.Data;
import Monitor.Numeric;
import alma.ACSErrTypeCommon.wrappers.AcsJUnexpectedExceptionEx;
import alma.acs.component.client.AdvancedComponentClient;
import alma.acs.component.client.ComponentClient;
import alma.acs.container.AcsManagerProxy;
import alma.acs.container.ContainerServices;
import alma.acs.exceptions.AcsJException;
import alma.acs.logging.AcsLogLevel;
import alma.acs.logging.ClientLogManager;
import alma.acs.nc.ArchiveConsumer;
import alma.acs.nc.Helper;
import alma.acs.util.StopWatch;

/**
 * @author jschwarz
 *
 * $Id: EventModel.java,v 1.26 2010/12/29 16:48:37 jschwarz Exp $
 */
public class EventModel {
	private final ORB orb;
	private final Logger m_logger;


	private final AdvancedComponentClient compClient;
	private final ContainerServices cs;
	private final Helper h;
	private final NamingContext nctx;
	private final AcsManagerProxy mproxy;
	private final EventChannelFactory nsvc;
	private final EventChannelFactory lsvc;	// For logging service
	private final static String eventGuiId = "eventGUI";
	private final EventChannelFactory alsvc;
	private final EventChannelFactory arsvc;
	private HashMap<String, EventChannel> channelMap; // maps each event channel name to the event channel
	private HashMap<String, int[]> lastConsumerAndSupplierCount;
	private static EventModel modelInstance;
	private ArrayList<AdminConsumer> consumers;
	private ArrayList<AdminConsumer> readyConsumers;
	private HashMap<String, AdminConsumer> consumerMap;
	private static DynAnyFactory dynAnyFactory = null;
	public static final int MAX_NUMBER_OF_CHANNELS = 100;
	private NotificationServiceMonitorControl[] nsmc;
	private ArchiveConsumer archiveConsumer;
	private AdvancedComponentClient acc;

	private EventModel() throws Exception {
		String connectionString;
		String managerHost;
		
		int acsInstance = 0;
		managerHost = "localhost";
		try {
			connectionString = System.getProperty("ACS.Manager",System.getenv("MANAGER_REFERENCE"));
			System.setProperty("ORBInitRef.NameService", System.getenv("ACS_NAME_SERVICE"));
			String temp = connectionString.substring("corbaloc::".length());
			int endIndex = temp.indexOf(":");
			managerHost = temp.substring(0, endIndex);
			acsInstance = (Integer.parseInt(temp.substring(endIndex+1, temp.indexOf("/"))) - 3000)/100;
		} catch (Exception e) {
			if ((connectionString = System.getProperty("ACS.Manager")) == null) { // Joe's Linux box in Garching is the default!
				acsInstance = 0;
				managerHost = "alma";
				connectionString = getConnectionString(managerHost, acsInstance);
			}
		}
		m_logger = ClientLogManager.getAcsLogManager().getLoggerForApplication(eventGuiId, false);
		ClientLogManager.getAcsLogManager().suppressRemoteLogging();
		acc = null;
		try {
			acc = new AdvancedComponentClient(m_logger, connectionString, eventGuiId) {
              @Override
               protected void initAlarmSystem() {
                   m_logger.info("The eventGUI suppresses initialization of the alarm system libraries, to cut the unnecessary dependency on CERN AS jar files.");
               } 
};
		} catch (Exception e) {
			if (PlatformUI.isWorkbenchRunning()) {
			MessageDialog dialog = new MessageDialog(null,"Can't create client",null,"The eventGUI client cannot be created. You might want to check the ACS host and instance.\n"+
					"ACS instance used: "+acsInstance+"; Looked for manager on host: "+managerHost,
			MessageDialog.ERROR, new String[]{"OK"}, 0);
			dialog.open();
			IStatus status = new Status(IStatus.ERROR, eventGuiId,0, "Couldn't create component client", e);
			Platform.getLog(Platform.getBundle(eventGuiId)).log(status);
			}
			else {
				System.out.println("Can't create advanced component client.");
				e.printStackTrace();
			}
			throw(e);
		}
		channelMap = new HashMap<String, EventChannel>(MAX_NUMBER_OF_CHANNELS);
		lastConsumerAndSupplierCount = new HashMap<String, int[]>(MAX_NUMBER_OF_CHANNELS);
		consumerMap = new HashMap<String, AdminConsumer>(MAX_NUMBER_OF_CHANNELS);
		consumers = new ArrayList<AdminConsumer>(MAX_NUMBER_OF_CHANNELS*5); // a guess at the possible limit to the number of consumers
		readyConsumers = new ArrayList<AdminConsumer>(MAX_NUMBER_OF_CHANNELS*5);
		compClient = acc;
		mproxy = compClient.getAcsManagerProxy();

		nsvc = EventChannelFactoryHelper.narrow(mproxy.get_service(alma.acscommon.NOTIFICATION_FACTORY_NAME.value, true));
		lsvc = EventChannelFactoryHelper.narrow(mproxy.get_service(alma.acscommon.LOGGING_NOTIFICATION_FACTORY_NAME.value, true));
		alsvc = EventChannelFactoryHelper.narrow(mproxy.get_service("AlarmNotifyEventChannelFactory", true));
		arsvc = EventChannelFactoryHelper.narrow(mproxy.get_service(alma.acscommon.ARCHIVE_NOTIFICATION_FACTORY_NAME.value, true));
		cs = compClient.getContainerServices();
		orb = compClient.getAcsCorba().getORB();
		
		dynAnyFactory = DynAnyFactoryHelper.narrow(orb.resolve_initial_references("DynAnyFactory"));
		
		h = new Helper(cs);
		nctx = h.getNamingService();
		nsmc = getMonitorControl();
//		getServiceTotals(); // temporarily, for testing
	}

	/**
	 * This routine returns an array of NotificationServiceMonitorControl objects (provided by the
	 * ACE/TAO Monitoring extensions) by resolving the IORs for these objects that are stored in
	 * the $ACS_TMP/ACS_INSTANCE.x/iors/ directory. 
	 * @throws NotFound
	 * @throws CannotProceed
	 * @throws InvalidName
	 */
	private NotificationServiceMonitorControl[] getMonitorControl() throws NotFound, CannotProceed,
			org.omg.CosNaming.NamingContextPackage.InvalidName {
		final String[] MC_IORS = {"NotifyMCIOR" };
		// final String[] MC_IORS = {"AlarmNotifyMCIOR", "ArchiveNotifyMCIOR", "LoggingNotifyMCIOR", "NotifyMCIOR" };
		NotificationServiceMonitorControl[] nsmc = new NotificationServiceMonitorControl[MC_IORS.length];
		String iorbase = System.getProperty("ACS.tmp");
		System.out.println("ACS_TMP:"+iorbase);
		String instdir = System.getenv("ACS_INSTANCE");
		if (instdir == null)
			instdir = "ACS_INSTANCE.0";
		else
			instdir = "ACS_INSTANCE."+instdir;
		iorbase += File.separator+instdir+File.separator+"iors"+File.separator;
		for (int i = 0; i < MC_IORS.length; i++) {
			String iorpath = iorbase + MC_IORS[i]; // NS_MC_IOR;
			System.out.println("IORPATH: " + iorpath);
			File iorFile = new File(iorpath);
			try {
				BufferedReader input = new BufferedReader(new FileReader(
						iorFile));
				String iorString = input.readLine();
				if (iorString != null)
					nsmc[i] = NotificationServiceMonitorControlHelper.narrow(orb
							.string_to_object(iorString));
				input.close();
			} catch (FileNotFoundException e) {
				e.printStackTrace();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
		return nsmc;
	}
	
	private String getConnectionString(String managerHost, int acsInstance) {
		String port = Integer.toString(3000+acsInstance*100);
		return "corbaloc::"+managerHost+":"+port+"/Manager";
	}
	
	public synchronized static EventModel getInstance() throws Exception {
		if (modelInstance == null) 
			modelInstance = new EventModel();
		return modelInstance;
	}
	
	public Logger getLogger() {
		return m_logger;
	}
	
	public ArrayList<ChannelData> getServiceTotals() {
		ArrayList<ChannelData> clist = new ArrayList<ChannelData>();
		final EventChannelFactory[] efacts = {nsvc, lsvc, alsvc, arsvc};
		final String[] efactNames = {"Notification", "Logging", "Alarm", "Property Archiving"};

		int nconsumers;
		int nsuppliers;
		for (int i = 0; i < efacts.length; i++) {
			int[] chans;
			chans = efacts[i].get_all_channels();
			nconsumers = 0;
			nsuppliers = 0;
			for (int j = 0; j < chans.length; j++) {
				try {
					nconsumers += efacts[i].get_event_channel(chans[j]) // TODO: These calculations depend on assumption that 1 consumer admin ==> 1 consumer
							.get_all_consumeradmins().length;
					nsuppliers += efacts[i].get_event_channel(chans[j])
							.get_all_supplieradmins().length;
				} catch (ChannelNotFound e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
//			System.out.printf("%s consumers: %d\n", efactNames[i], nconsumers);
//			System.out.printf("%s suppliers: %d\n", efactNames[i], nsuppliers);
//			System.out.printf("Number of channels for: %s %d \n", efactNames[i],
//					chans.length);
			clist.add(new ChannelData(efactNames[i], new int[]{nconsumers, nsuppliers},new int[]{0,0}));
			lastConsumerAndSupplierCount.put(efactNames[i], new int[]{0,0});
		}

		return clist;
	}
	
	public ArrayList<ChannelData> getChannelStatistics() {
		ArrayList<ChannelData> clist = new ArrayList<ChannelData>();
		BindingListHolder bl = new BindingListHolder();
		BindingIteratorHolder bi = new BindingIteratorHolder();
		final String[] roleNames = {"consumer","supplier"};
		
		nctx.list(-1, bl, bi);
		for (Binding binding : bl.value) {
			String serviceKind = alma.acscommon.NC_KIND.value;
			if (binding.binding_name[0].kind.equals(serviceKind)) {
				String channelName = binding.binding_name[0].id;
				EventChannel ec;
				try {
					ec = getNotificationChannel(channelName, alma.acscommon.NC_KIND.value);

					AdminConsumer consumer = null;
					int[] consAndSupp = {0,0};
					if (!channelMap.containsKey(channelName)) {
						channelMap.put(channelName, ec);
						consumer = getAdminConsumer(channelName);
						consumers.add(consumer);
						lastConsumerAndSupplierCount.put(channelName,consAndSupp);
					} else {
						if (lastConsumerAndSupplierCount.containsKey(channelName))
							consAndSupp = lastConsumerAndSupplierCount.get(channelName);
					}
					int [] adminCounts = new int[2];
					int [] adminDeltas = new int[2];
					adminCounts[0] = ec.get_all_consumeradmins().length;
					adminCounts[1] = ec.get_all_supplieradmins().length;

					for (int i = 0; i < adminCounts.length; i++) {
						String cstr = channelName;
						int cdiff = adminCounts[i] - consAndSupp[i];
						if (cdiff != 0) {
							if (cdiff > 0) {
								cstr += " has added " + cdiff + " "
										+ roleNames[i];
							} else if (cdiff < 0) {
								cstr += " has removed " + (-cdiff) + " "
										+ roleNames[i];
							}
							cstr += (Math.abs(cdiff)!=1 ? "s." : ".");
							m_logger.info(cstr);
						}
						adminDeltas[i] = cdiff;
					}
					lastConsumerAndSupplierCount.put(channelName,adminCounts);
					m_logger.info("Channel: "+channelName+" has "+adminCounts[0]+" consumers and "+adminCounts[1]+" suppliers.");
					clist.add(new ChannelData(channelName, adminCounts, adminDeltas));
				} catch (AcsJException e) {
					m_logger.log(AcsLogLevel.SEVERE, "Can't find channel"+channelName, e);
				}

			}
//			try {
//				printMonitoringResults(nsmc);
//			} catch (InvalidName e) {
//				// TODO Auto-generated catch block
//				e.printStackTrace();
//			}
		}
		return clist;	
	}
	
	/**
	 * This method gets a reference to the event channel. If it is not already
	 * registered with the naming service, it is created.
	 * 
	 * @return Reference to the event channel specified by channelName.
	 * @param channelName
	 *           Name of the event channel registered with the CORBA Naming
	 *           Service
	 * @param channelKind
	 *           Kind of the channel as registered with the CORBA naming service.
	 * COMMENTED OUT: @param notifyFactoryName
	 *           Name of the notification service as registered with the CORBA
	 *           naming service.
	 * @throws AcsJException
	 *            Standard ACS Java exception.
	 */
	protected EventChannel getNotificationChannel(String channelName, String channelKind) 
		throws AcsJException 
	{
		// return value
		EventChannel retValue = null;

		try {
//			m_logger.fine("Will create notification channel " + channelName);
			NameComponent[] t_NameSequence = { new NameComponent(channelName, channelKind) };
			retValue = EventChannelHelper.narrow(nctx.resolve(t_NameSequence));
		} 
		catch (org.omg.CosNaming.NamingContextPackage.NotFound e) {
			// No other suppliers have created the channel yet...create it
			m_logger.info("The " + channelName + " channel has not been created yet.");
//			return createNotificationChannel(channelName, channelKind, notifyFactoryName);
			throw new AcsJUnexpectedExceptionEx(e);
		} 
		catch (org.omg.CosNaming.NamingContextPackage.CannotProceed e) {
			// Think there is virtually no chance of this every happening but...
			throw new AcsJUnexpectedExceptionEx(e);
		} 
		catch (org.omg.CosNaming.NamingContextPackage.InvalidName e) {
			// Think there is virtually no chance of this every happening but...
			throw new AcsJUnexpectedExceptionEx(e);
		}
		
		return retValue;
	}
	
	public String[] getServices() {

		return orb.list_initial_services();
	}
	
	public ContainerServices getContainerServices() {
		return cs;
	}
	
	public void refreshChannelSubscriptions() {
		consumers = getAllConsumers();

		if (consumers != null) {
			for (AdminConsumer consumer : consumers) {
				try {
					if (!readyConsumers.contains(consumer)) {
						consumer.consumerReady();
						readyConsumers.add(consumer);
					}
				} catch (AcsJException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}
		}
	}


	public AdminConsumer getAdminConsumer(String channelName) throws AcsJException {
		if (!consumerMap.containsKey(channelName)) {
			AdminConsumer adm = new AdminConsumer(channelName,cs);
			consumerMap.put(channelName, adm);
			return adm;
		}
		return consumerMap.get(channelName);
	}

	public ArrayList<AdminConsumer> getAllConsumers() {
		int channelsProcessed = 0;
		StopWatch sw = new StopWatch(m_logger);
		BindingListHolder bl = new BindingListHolder();
		BindingIteratorHolder bi = new BindingIteratorHolder();
		nctx.list(-1, bl, bi);
		for (Binding binding : bl.value) {
			String serviceKind = alma.acscommon.NC_KIND.value;
			if (binding.binding_name[0].kind.equals(serviceKind)) {
				String channelName = binding.binding_name[0].id;
				System.out.println("Channel: "+channelName);
				EventChannel ec;
				try {
					ec = getNotificationChannel(channelName, alma.acscommon.NC_KIND.value);

					AdminConsumer consumer = null;
					if (!channelMap.containsKey(channelName)) {
						channelMap.put(channelName, ec);
						consumer = getAdminConsumer(channelName);
						consumers.add(consumer);
						channelsProcessed++;
					}
				} catch (AcsJException e) {
					m_logger.log(AcsLogLevel.SEVERE, "Can't find channel"+channelName, e);
				}
			}
		}
		sw.logLapTime(" to create "+channelsProcessed+" channels ");
		getArchiveConsumer();
		return consumers;
	}

	public void getArchiveConsumer() {
		synchronized (this ){
			if (archiveConsumer == null)
				try {
					archiveConsumer = new ArchiveConsumer(cs,new ArchiveReceiver());
					archiveConsumer.consumerReady();
				} catch (AcsJException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		}
	}
	
	public static DynAnyFactory getDynAnyFactory() {
		return dynAnyFactory;
	}
	
	private void printMonitoringResults(NotificationServiceMonitorControl[] mc) throws InvalidName { // /alma/ACS-9.0/TAO/ACE_wrappers/build/linux/TAO/orbsvcs/orbsvcs/Notify/MonitorControlExt/NotifyMonitoringExt.idl
		for (int i = 0; i < mc.length; i++) {
			String[] names = mc[i].get_statistic_names();
			for (int j = 0; j < names.length; j++) {
				//m_logger.info("NC Statistic name[" + j + "] : " + names[j]);
				if (!names[j].contains("/"))  // the max index can be zero!!!
					break;
				String channel = names[j].split("/")[1];
				Data stats = mc[i].get_statistic(names[j]);

				if (names[j].endsWith("ConsumerNames")) {
					String[] consumers = stats.data_union.list();
					System.out.println("Consumers for "+channel);
					for (int k = 0; k < consumers.length; k++) {
						System.out.println("\t"+consumers[k]);
					}
				}
				else if (names[j].endsWith("QueueElementCount")) {
					System.out.println("QueueElementCount for "+channel);
					Numeric numbers = stats.data_union.num();
					System.out.println("\tCount " + numbers.count);
					System.out.println("\tAverage " + numbers.average);
					System.out.println("\tSum of squares " + numbers.sum_of_squares);
					System.out.println("\tMinimum " + numbers.minimum);
					System.out.println("\tMaximum " + numbers.maximum);
					System.out.println("\tLast " + numbers.last);
				}

			}
		}

	}

	public void closeAllConsumers() {
		//ArrayList<AdminConsumer>consumers = getAllConsumers();
		for (AdminConsumer consumer : consumers) {
			if (consumer != null) {
				consumer.disconnect();
			}
		}
	}
	
	public void closeArchiveConsumer() {
		if (archiveConsumer != null)
			archiveConsumer.disconnect();
	}

	public void tearDown() {
		try {
			closeAllConsumers();
			closeArchiveConsumer();
			acc.tearDown();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
}
