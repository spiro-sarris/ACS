/*
 *    ALMA - Atacama Large Millimiter Array
 *    (c) European Southern Observatory, 2009
 *    Copyright by ESO (in the framework of the ALMA collaboration)
 *    and Cosylab 200, All rights reserved
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
package alma.acs.logging.tools;

import com.cosylab.logging.engine.log.ILogEntry;

/**
 * Convert a log into a twiki table (ASCII).
 * <P> 
 * The formatted string is composed of plain ASCII, the fields are
 * separated by a '|'.
 * <P>
 * The processing is done by delegating to the parent CSVConverter. 
 * 
 * @author acaproni
 * @since ACS 8.1.0
 */
public class TwikiTableConverter extends CSVConverter {

	/**
	 * Constructor
	 * 
	 * @param cols The columns to write in the converted string
	 * @see LogConverter#colIndex
	 */
	public TwikiTableConverter(String cols) {
		super(cols,'|',false);
	}
	
	/**
	 * Convert the log into a String
	 */
	public String convert(ILogEntry log) {
		String ret=super.convert(log);
		return "|"+ret.substring(0, ret.length()-1)+"|\n";
	}

	/**
	 * @see alma.acs.logging.tools.CSVConverter#getHeader()
	 */
	@Override
	public String getHeader() {
		String ret=super.getHeader();
		ret=ret.replaceAll("\\|", "* | *");
		String hdr = "| *"+ret.substring(0, ret.length()-1)+"* |\n";
		return hdr;
	}
	
	
}
