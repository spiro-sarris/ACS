package com.cosylab.logging.settings;

import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Frame;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JFileChooser;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JRootPane;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JToolBar;
import javax.swing.SwingUtilities;
import javax.swing.text.BadLocationException;
import javax.swing.text.PlainDocument;

import com.cosylab.logging.engine.log.LogTypeHelper;

/**
 * The dialog to show the errors.
 * <P>
 * The dialog stores errors till maxLength chars is reached. 
 * If the log exceeds that number, they are automatically flushed in 
 * a file in <code>ACS_TMP</code> that is not be deleted when jlog terminates.
 * <BR>
 * If an error happened while creating the file, the errors are not flushed on disk
 * and therefore the only part of the errors that can be saved is that in the text area.
 * <P>
 * The dimension defaults to <code>ERROR_LOG_DEFAULT_SIZE</code> and can be changed setting
 * the <code>ERRORLOG_SIZE_PROP_NAME</code> property.
 * <P>
 * The content of the dialog can be saved and cleared.
 * 
 * 
 * @author acaproni
 *
 */
public class ErrorLogDialog extends JDialog implements ActionListener {
	
	/**  
	 * The log text appears into a <code>JtextArea</code>
	 */
	private JTextArea logTA;
	
	/**
	 *  The document of the TextArea
	 */
	private PlainDocument document = new PlainDocument();
	
	/**
	 *  The button to close (hide) the dialog
	 */
	private JButton closeBtn;
	
	/**
	 * The button to erase all the logs (i.e. the logs shown in the window and 
	 * those flushed on the temporary file)
	 */
	private JButton cleanAllBtn;
	
	
	/**
	 * / The button to save all the logs in a file (it saves the content of the 
	 * temporary log file on disk and the content of the text area)
	 * <P>
	 * The button is enabled only if some log has been flushed on disk
	 */
	private JButton saveAllBtn;
	
	/**
	 *  The toolbar
	 */
	private JToolBar toolBar;
	
	/**
	 * The maximum dimension of the log to keep in memory.
	 * <P>
	 * Its value is read from a property.
	 * If the value is 0, the error log is unlimited
	 */
	private long maxLength;
	
	/**
	 * / The name of the property defining the size of the error log
	 */
	private final String ERRORLOG_SIZE_PROP_NAME = "jlog.errorlog.size";
	
	/**
	 * / The default maximum size of the ERROR LOG
	 */
	private final long ERROR_LOG_DEFAULT_SIZE = 50 *1000000;
	
	/**
	 * The file to flush logs is created only if there is a log to flush
	 */
	private File tmpFile = null;
	
	/**
	 * The output stream
	 */
	private FileOutputStream outF=null;
	
	/**
	 * Remember if there was an error creating the temporary file for 
	 * flushing errors.
	 * <P>
	 * In case an error happened creating the temporary file, the dialog 
	 * does not try to create a new file again and therefore
	 * the flushed strings will be lost.
	 * 
	 */
	private boolean errorCreatingTmpFile=false;
	
	/**
	 * Constructor
	 * 
	 * @param owner The owner of the dialog
	 * @param title The title
	 * @param modal Modal type
	 */
	public ErrorLogDialog(Frame owner, String title, boolean modal) {
		super(owner, title, modal);
		this.setDefaultCloseOperation(HIDE_ON_CLOSE);
		initGUI();
		pack();
		maxLength = Long.getLong(ERRORLOG_SIZE_PROP_NAME, ERROR_LOG_DEFAULT_SIZE);
		System.out.println("Max length of in-memory error log "+maxLength);
		setVisible(false);
		toFront();
	}
	
	/**
	 * Builds the content of the GUI
	 *
	 */
	private void initGUI() {
		ImageIcon icon = new ImageIcon(LogTypeHelper.class.getResource("/errorLogIcon.png"));
		setIconImage(icon.getImage());
		
		logTA = new JTextArea("", 20, 60);
		synchronized(logTA) {
			logTA.setDocument(document);
			logTA.setEditable(false);
		}
		JScrollPane logSP = new JScrollPane(logTA);
		
		JRootPane mainPnl = this.getRootPane();
		mainPnl.setLayout(new BorderLayout());
		
		mainPnl.add(logSP,BorderLayout.CENTER);
		
		// Close button
		JPanel btnPnl = new JPanel(new FlowLayout());
		closeBtn = new JButton("Close");
		closeBtn.addActionListener(this);
		btnPnl.add(closeBtn);
		
		mainPnl.add(btnPnl,BorderLayout.SOUTH);
		
		
		// Build the toolbar
		toolBar = new JToolBar();
		JPanel toolBarPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
		ImageIcon cleanIcon=new ImageIcon(ErrorLogDialog.class.getResource("/delete.png"));
		cleanAllBtn = new JButton("<HTML><Font size=\"-1\">Clean</FONT></HTML>",cleanIcon);
		cleanAllBtn.addActionListener(this);
		cleanAllBtn.setToolTipText("Delete log");
		ImageIcon saveIcon=new ImageIcon(ErrorLogDialog.class.getResource("/disk.png"));
		saveAllBtn = new JButton("<HTML><Font size=\"-1\">Save</FONT></HTML>",saveIcon);
		saveAllBtn.addActionListener(this);
		saveAllBtn.setToolTipText("Save log");
		
		toolBarPanel.add(cleanAllBtn);
		toolBarPanel.add(saveAllBtn);
		
		toolBar.add(toolBarPanel);
		mainPnl.add(toolBar, BorderLayout.PAGE_START);
		
		rationalizeButtons();
	}
	
	/**
	 * Add a String to the error log and show/hide the dialog
	 * if it is the first time an error is added
	 * 
	 * @param str The string to append in the TextArea
	 * @param show Show/hide the dialog
	 */
	public synchronized void appendText(String str) {
		class RunAsyncAppend implements Runnable {
			private String theString;
			
			public RunAsyncAppend(String str) {
				theString=str;
			}
			
			public void run() {
				int len = document.getLength();
				// Check the number of chars in the widget
				synchronized(logTA) {
					if (maxLength>0 && len>maxLength) {
						// Flush some chars in the file
						String strToFlush;
						try {
							strToFlush = logTA.getText(0, theString.length());
						} catch (BadLocationException ble) {
							System.out.println("Error removing text from the TextArea: "+ble.getMessage());
							ble.printStackTrace();
							return;
						}
						logTA.replaceRange("", 0, theString.length());
						flush(strToFlush);
					}
					logTA.append(theString);
				}
				rationalizeButtons();
			}
		};
		
		RunAsyncAppend runAppend = new RunAsyncAppend(str);
		SwingUtilities.invokeLater(runAppend);
	}
	
	
	/**
	 * Clear the log in the windows and the log in the file
	 *
	 */
	public synchronized void clearAll() {
		Runnable clearTA = new Runnable() {
			public void run() {
				synchronized (logTA) {
					if (document.getLength()>0) {
						logTA.replaceRange("", 0, document.getLength());
					}
				}
			}
		};
		SwingUtilities.invokeLater(clearTA);
		try {
			if (outF!=null) {
				outF.close();
			}
		} catch (IOException ioe) {
			System.out.println("Exception deleting temporary file: "+ioe.getMessage());
			ioe.printStackTrace();
		}
		outF=null;
		tmpFile=null;
		rationalizeButtons();
	}
	
	/**
	 * @see java.awt.event.ActionListener
	 * @see java.awt.event.ActionEvent
	 */
	public void actionPerformed(ActionEvent e) {
		if (e.getSource()==closeBtn) {
			setVisible(false);
		} else if (e.getSource()==saveAllBtn) {
			saveAllLog();
		} else if (e.getSource()==cleanAllBtn) {
			clearAll();
		} else {
			System.err.println("Action unknown");
		}
	}
	
	/**
	 * Save the content of the temporary file and the content of the text area 
	 * into a file
	 *
	 */
	private void saveAllLog() {
		File f=null;
		JFileChooser chooser = new JFileChooser();
		chooser.setMultiSelectionEnabled(false);
		chooser.setDialogTitle("Save error log");
		int returnVal = chooser.showOpenDialog(this);
	    if(returnVal == JFileChooser.APPROVE_OPTION) {
	    	f = chooser.getSelectedFile();
	    } else {
	    	return;
	    }
	    FileOutputStream fStream=null;
	    try {
	    	fStream = new FileOutputStream(f);
	    } catch (FileNotFoundException fnfe) {
	    	JOptionPane.showMessageDialog(this, "Error opening the file", "Error saving the log", JOptionPane.ERROR_MESSAGE);
	    	System.out.println(fnfe.getMessage());
    		fnfe.printStackTrace();
	    	return;
	    }
	    BufferedOutputStream bufOutStream = new BufferedOutputStream(fStream);
	    
	    if (tmpFile!=null) {
		    FileInputStream inF =null;
		    try {
		    	inF= new FileInputStream(tmpFile);
		    } catch (IOException ioe) {
		    	System.out.println("Error opening the log on disk: "+ioe.getMessage());
		    	JOptionPane.showMessageDialog(this, "Error opening the input file", "Error saving the log", JOptionPane.ERROR_MESSAGE);
		    	ioe.printStackTrace();
		    	return;
		    }
		    
		    // Copy the content of the temporary file
		    byte[] buffer = new byte[512];
		    
	    	int bytesRead;
	    	do {
	    		try {
	    			bytesRead=inF.read(buffer);
	    		}  catch (IOException ioe) {
	    	    	System.out.println("Error reading from the log on disk: "+ioe.getMessage());
	    	    	JOptionPane.showMessageDialog(this, "Error reading log from disk", "Error saving the log", JOptionPane.ERROR_MESSAGE);
	    	    	ioe.printStackTrace();
	    	    	return;
	    	    }
	    		if (bytesRead>0) {
	    			try {
	    				bufOutStream.write(buffer, 0, bytesRead);
	    			}  catch (IOException ioe) {
	    		    	System.out.println("Error writing on file: "+ioe.getMessage());
	    		    	JOptionPane.showMessageDialog(this, "Error writing on file", "Error saving the log", JOptionPane.ERROR_MESSAGE);
	    		    	ioe.printStackTrace();
	    		    	return;
	    		    }
	    		}
	    	} while (bytesRead>=0);
	    }
	    
	    // Write the content of the window
	    synchronized (logTA) {
	    	try {
	    		bufOutStream.write(logTA.getText().getBytes());
	    	} catch (IOException ioe) {
	    		JOptionPane.showMessageDialog(this, "Error writing on file", "Error saving the log", JOptionPane.ERROR_MESSAGE);
	    		System.out.println(ioe.getMessage());
	    		ioe.printStackTrace();
	    		return;
	    	}
	    }
	    try {
	    	bufOutStream.flush();
	    	bufOutStream.close();
	    } catch (IOException ioe) {
    		JOptionPane.showMessageDialog(this, "Error closing the file", "Error saving the log", JOptionPane.ERROR_MESSAGE);
    		System.out.println(ioe.getMessage());
    		ioe.printStackTrace();
    		return;
    	}
	}
	
	/**
	 * Write the given string on the file
	 * 
	 * @param str The string to flush
	 */
	private void flush(String str) {
		if (errorCreatingTmpFile) {
			// There was an error creating the temporary file:
			// the flushing is disabled
			return;
		}
		if (outF==null) {
			try {
				initTmpFile();
			} catch (IOException ioe) {
				System.out.println("Error creating the temporary log file: "+ioe.getMessage());
				ioe.printStackTrace();
				errorCreatingTmpFile=true;
				JOptionPane.showInternalMessageDialog(
						logTA, 
						"<HTML>Error creating the temporary file: <I>"+
						ioe.getMessage()+
						"</I><BR>saving is limited to the content of the text area.</HTML>", 
						"Error creating a file", 
						JOptionPane.INFORMATION_MESSAGE);
				return;
			}
		}
		try {
			outF.write(str.getBytes());
		} catch (IOException ioe) {
			System.out.println("Error writing to the temporary log file: "+ioe.getMessage());
			ioe.printStackTrace();
		}
	}
	
	/**
	 * Create the temporary file for flushing the log
	 * 
	 * @return The newly create file
	 * 
	 * @throws IOException 
	 */
	private void initTmpFile() throws IOException {
		// Get a name for the file
		String tmpDir = System.getProperty("ACS.tmp");
		if (tmpDir==null || tmpDir.length()==0) {
			tmpDir = ".";
		}
		File dir = new File(tmpDir);
		tmpFile = File.createTempFile("jlog.", ".error.log", dir);
		tmpFile.deleteOnExit();
		outF = new FileOutputStream(tmpFile);
	}
	
	/**
	 * Flush and close the file when the object is destroyed by the GC
	 */
	protected void finalize() throws Throwable {
		if (outF!=null) {
			outF.flush();
			outF.close();
			outF=null;
		}
		outF=null;
		tmpFile=null;
		super.finalize();
	}
	
	/**
	 * Enable/Disable the buttons in the toolbar depending on the
	 * content of the text area and the existence of the temporary
	 * file
	 */
	private void rationalizeButtons() {
		Runnable ratio = new Runnable() {
			public void run() {
				saveAllBtn.setEnabled(document.getLength()>0);
				cleanAllBtn.setEnabled(document.getLength()>0);
			}
		};
		SwingUtilities.invokeLater(ratio);
	}
}
