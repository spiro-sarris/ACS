/*
 * Created on Dec 18, 2004
 *
 * TODO To change the template for this generated file go to
 * Window - Preferences - Java - Code Style - Code Templates
 */
package com.cosylab.logging.client;

import java.awt.Component;
import java.util.Vector;

import javax.swing.JComponent;
import javax.swing.JTable;
import javax.swing.table.AbstractTableModel;
import javax.swing.table.TableCellRenderer;
import javax.swing.table.TableModel;

import com.cosylab.logging.engine.log.ILogEntry;

/**
 * The table used to represent data in the right panel of the
 * main window
 * 
 * @author acaproni
 *
 */
public class DomTable extends JTable 
{
	int rowsNum; // The rows in the table
	String[][] nameValue; // The pair <name,value>
	
	private TableModel dataModel = new AbstractTableModel() { 
		
		public int getColumnCount()
		{
			return 2;
		}
		public int getRowCount()
		{
			return rowsNum;
		}
		public Object getValueAt(int row, int col)
		{
			return nameValue[row][col];
		}
	};

	/**
	 * Build a table using the dats in the log entry
	 * 
	 * @param log The logEntry with the datas to display 
	 */
	public DomTable(ILogEntry log) throws Exception {
		super();

		if (!log.hasDatas()) {
			throw new Exception(); //getDomTree();
		} 

		//	gets the number of the "data" elements for the selected row
		Vector<ILogEntry.AdditionalData> additionalData = log.getAdditionalData();
		rowsNum = additionalData.size();

		if (rowsNum > 0) {
			nameValue = new String[rowsNum][2];
			for (int i = 0; i < rowsNum; i++) {
				nameValue[i][0] = additionalData.get(i).getName();
				nameValue[i][1] = additionalData.get(i).getValue();
			}

			setModel(dataModel);

			// Change the name of the columns
			getColumnModel().getColumn(0).setHeaderValue("Name");
			getColumnModel().getColumn(1).setHeaderValue("Value");

			// Force the header to resize and repaint itself
			getTableHeader().resizeAndRepaint();
		}
	}
	
	/**
	 * Sets a tool tip on all the cells. It pops up when the value is not fully displayed while the mose 
	 * scrolls over it. 
	 * @see javax.swing.JTable#prepareRenderer(TableCellRenderer, int, int)
	 */
	public Component prepareRenderer(TableCellRenderer renderer, int rowIndex, int vColIndex)
	{
		Component c = super.prepareRenderer(renderer, rowIndex, vColIndex);

		int columnWidth = getColumnModel().getColumn(vColIndex).getWidth() / 6;
		setToolTip((JComponent)c,nameValue[rowIndex][vColIndex],columnWidth);
		return c;
	}
	
	/**
	 * Format the string before setting the tooltip for the given component
	 * The tooltip is shown only if the text is not visible (i.e. the num.
	 * of displayed chars for the column containing the text is less then
	 * the given text).
	 * 
	 * To show the string as multine it is transformed in HTML so
	 * \n are replaced by <BR>/ To show strings containing HTML and/or
	 * XML the <PRE> tag is used (for this reason existing < and > in
	 * the original string are replaced by &lt; and &lgt;)
	 * 
	 * @param c The component to set the tooltip 
	 * @param text The string to display in the tooltip
	 * @param colWidth The width of the column
	 * 
	 * @return
	 */
	private void setToolTip(JComponent  c, String text, int colWidth) {
		if (text==null)	((JComponent) c).setToolTipText(null);
		else if (text.length() <colWidth) ((JComponent) c).setToolTipText(null);
		else {
			// I am going to print the string in HTML format: new lines become <BR>
			text=text.replaceAll("<","&lt;");
			text=text.replaceAll(">","&gt;");
			// Eventually, set the tooltip
			((JComponent) c).setToolTipText("<HTML><PRE>"+text+"</PRE></HTML>");
		}
	}

}
