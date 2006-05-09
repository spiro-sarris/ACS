package alma.acs.logging.config;

import java.util.HashMap;
import java.util.Map;

import com.cosylab.CDB.DALChangeListener;
import com.cosylab.CDB.DALOperations;
import com.cosylab.CDB.DAO;
import com.cosylab.CDB.RecordDoesNotExist;
import com.cosylab.CDB.XMLerror;

/**
 * 
 * @author hsommer
 */
public class TestCDB implements DALOperations {

	private Map<String, String> curlToXmlMap = new HashMap<String, String>();
	private boolean throwEx = false;
	
    ////////////////////////////////////////////////////
    // Test setup methods
    ////////////////////////////////////////////////////

	String addCurlToXmlMapping(String curl, String xml) {
		return curlToXmlMap.put(curl, xml);
	}
	
	String removeCurl(String curl) {
		return curlToXmlMap.remove(curl);
	}
	
	void setThrowException(boolean throwEx) {
		this.throwEx = throwEx;
	}
	
    ////////////////////////////////////////////////////
    // Implementation of DALOperations
    ////////////////////////////////////////////////////

	/** 
	 * Test impl of the only CDB method which actually gets used by the logging config classes.
	 */
	public String get_DAO(String curl) throws XMLerror, RecordDoesNotExist {
		if (throwEx) {
			throw new RecordDoesNotExist("This is a test exception.");
		}
		return curlToXmlMap.get(curl);
	}

    ////////////////////////////////////////////////////
    // Dummy impl of unused methods from the interface
    ////////////////////////////////////////////////////

	public DAO get_DAO_Servant(String curl) throws XMLerror, RecordDoesNotExist {
		throw new IllegalStateException("Operation not implemented!");
	}

	public void shutdown() {
		throw new IllegalStateException("Operation not implemented!");
	}

	public int add_change_listener(DALChangeListener listener) {
		throw new IllegalStateException("Operation not implemented!");
	}

	public void listen_for_changes(String curl, int listenerID) {
		throw new IllegalStateException("Operation not implemented!");
	}

	public void remove_change_listener(int listenerID) {
		throw new IllegalStateException("Operation not implemented!");
	}

	public String list_nodes(String name) {
		throw new IllegalStateException("Operation not implemented!");
	}
}
