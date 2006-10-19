/*
 *    ALMA - Atacama Large Millimiter Array
 *    (c) European Southern Observatory, 2002
 *    Copyright by ESO (in the framework of the ALMA collaboration)
 *    and Cosylab 2002, All rights reserved
 *
 *    This library is free software; you can redistribute it and/or
 *    modify it under the terms of the GNU Lesser General Public
 *    License as published by the Free Software Foundation; either
 *    version 2.1 of the License, or (at your option) any later version.
 *
 *    This library is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *    Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with this library; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
 *    MA 02111-1307  USA
 */
package alma.acs.logging.archive;

import javax.swing.ImageIcon;

import com.cosylab.logging.LoggingClient;

import java.lang.reflect.Constructor;
import java.lang.reflect.Method;
import java.util.logging.Logger;

/**
 * A class to connect and interact with the archive
 * 
 * The connection with the database is not always available.
 * There are 2 possibilities:
 * 	1. the code to connect to the DB is not available (it comes from
 * 	   a module in ARCHIVE)
 *  2. the code is availbale but for some reason something in the
 *     communication with the DB doesn't work as expected
 *     
 * @author acaproni
 *
 */
public class ArchiveConnectionManager {
	
	// The name of the class, the method and so on to load
	// dinamycally
	// (they are all generated by ARCHIVE and could not be
	// present at run time
	private final String ARCHIVE_CLASS_NAME = "alma.archive.logging.ArchiveLoggingQuery";
	private final String METHOD_NAME = "getLog";
	
	// The possible states of the database
	public static final int DATABASE_OK = 0;
	public static final int DATABASE_NOP = 1;
	public static final int DATABASE_WORKING =2;
	
	// The status of the connection with the DB
	// It can be DATABASE_OK, DATABASE_NOP, ...
	private int status;
	
	// The class to talk to the archive
	private Object archive = null;
	
	// The method to get logs from the database
	private Method getLogMethod;
	
	private LoggingClient logging;
	
	// The icons showed in the main window
	private ImageIcon[] databaseStatusIcons = new ImageIcon[] {
			new ImageIcon(ArchiveConnectionManager.class.getResource("/databaseLink.png")),
			new ImageIcon(ArchiveConnectionManager.class.getResource("/databaseNOP.png")),
			new ImageIcon(ArchiveConnectionManager.class.getResource("/databaseBusy.png"))
	};
	
	public ArchiveConnectionManager(LoggingClient loggingClient) {
		if (loggingClient==null) {
			throw new IllegalArgumentException("Invalid null LoggingClient reference");
		}
		logging = loggingClient;
		archive = loadArchiveClass();
		if (archive==null) {
			// The code for the archive is not availbale
			status = DATABASE_NOP;
			showDBStatus("Database connection not available");
		} else {
			getLogMethod = getMethod(archive);
			if (getLogMethod==null) {
				// The method for the archive is not availbale
				status = DATABASE_NOP;
				showDBStatus("Database connection not available");
			} else {
				status = DATABASE_OK;
				showDBStatus("Database ready");
			}
		}
	}
	
	/**
	 * Load the class to talk with the archive
	 * 
	 * @return An object to submit wueries to the database
	 *         null if something went wrong loading the class
	 */
	private Object loadArchiveClass() {
		try {
			  Thread t = Thread.currentThread();
			  ClassLoader loader = t.getContextClassLoader();
			  Class cl =loader.loadClass(ARCHIVE_CLASS_NAME);
			  Class[] classes = { Class.forName("java.util.logging.Logger")};
			  Constructor constructor = cl.getConstructor(classes);
			  Object obj = constructor.newInstance((Logger)null);
			  return cl.cast(obj);
		  } catch (Throwable t) {
			  System.out.println("alma.archive.logging.ArchiveLoggingQuery not found:");
			  System.out.println("\tDatabase connection not available "+t.getMessage());
			  t.printStackTrace();
			  return null;
		  }
	}
	
	/**
	 * Get the method to retrieve log from the database
	 * 
	 * @param obj The object containing the method
	 * @return The getLog method of the object
	 */
	private Method getMethod(Object obj) {
		if (obj==null) {
			throw new IllegalArgumentException("Invalid null parameter in getMethod");
		}
		Method ret = null;
		Class cl = obj.getClass();
		try {
			cl = Class.forName(ARCHIVE_CLASS_NAME);
		} catch (ClassNotFoundException cnfe) {
			System.out.println("Class not found: "+cnfe.getMessage());
			return null;
		}
		Class[] paramClasses=null;
		// Build the list of parameters
		try {
			paramClasses = new Class[] {
					Class.forName("java.lang.String"), //  String timeFrom
					Class.forName("java.lang.String"), // String timeTo
					java.lang.Short.TYPE, //  short minType
					java.lang.Short.TYPE, //short maxType, 
					Class.forName("java.lang.String"), // String routine
					Class.forName("java.lang.String"), // String source
					Class.forName("java.lang.String"), //String process
					java.lang.Integer.TYPE //, int maxRow
				};
		} catch (Exception e) {
			System.out.println("Error building the array of parameters:"+e.getMessage());
			e.printStackTrace();
			return null;
		}
		// Look for the given method
		try {
			ret = cl.getMethod(METHOD_NAME,paramClasses);
		} catch (Throwable t) {
			System.out.println("This mehtod does not exist in "+cl.getName());
			System.out.println("\t"+METHOD_NAME+"(");
			for (int temp=0; temp<paramClasses.length; temp++) {
				System.out.println("\t\t"+paramClasses[temp].getName()+",");
			}
			
			System.out.println("\t\t(\n\tDatabase connection not available:\n"+t.getMessage());
			t.printStackTrace();
		}
		return ret;
	}
	
	/**
	 * Notify the LoggingClient about the status of the connection with the database
	 * 
	 * The icon in the LC is set depending on the actual state of the connection.
	 * The tooltip of the icon is set equal to the msg parameter
	 * 
	 * @param msg A message to show as tool tip in the icon of the status
	 *            of the DB connection
	 */
	private void showDBStatus(String msg) {
		logging.showDBStatus(databaseStatusIcons[status],msg);
	}
	
	/**
	 * 
	 * @return The status of the DB
	 */
	public int getDBStatus() {
		return status;
	}
		
}
