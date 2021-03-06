#*******************************************************************************
# ALMA - Atacama Large Millimeter Array
# Copyright (c) ESO - European Southern Observatory, 2011
# (in the framework of the ALMA collaboration).
# All rights reserved.
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#*******************************************************************************
#*******************************************************************************
# PPPPPPPP
#
# "@(#) $Id: Makefile,v 1.18 2012/04/05 13:23:34 acaproni Exp $"
#
# Makefile of ........
#
# who       when      what
# --------  --------  ----------------------------------------------
# sharring  19/10/05  created
#

#*******************************************************************************
# This Makefile follows VLT Standards (see Makefile(5) for more).
#*******************************************************************************
# REMARKS
#    None
#------------------------------------------------------------------------

#
# user definable C-compilation flags
USER_CFLAGS = -rdynamic 

#
# additional include and library search paths
#USER_INC = 
USER_LIB =
# -lstdc++ -lxerces-c -lacscomponent

#
# MODULE CODE DESCRIPTION:
# ------------------------
# As a general rule:  public file are "cleaned" and "installed"  
#                     local (_L) are not "installed".

#
# C programs (public and local)
# -----------------------------
EXECUTABLES     = alarmSystemClient
EXECUTABLES_L   = testDriver testDriverMultiThreaded FactoryTestCase testXML testXML_2

alarmSystemClient_OBJECTS	= alarmSystemClient
alarmSystemClient_LIBS		= maciClient

# <brief description of xxxxx program>
FactoryTestCase_OBJECTS  = FactoryTestCase 
FactoryTestCase_LIBS     = acsErrTypeAlarmSourceFactory cdb cppunit logging acsAlSysSource maciErrType laserSourceAcsSpecific

# <brief description of xxxxx program>
testDriverMultiThreaded_OBJECTS   = testDriverMultiThreaded
testDriverMultiThreaded_LIBS      = AlarmTestMountMultiThreadedImpl testCppAlarmSourceComponentsStubs maciClient AcsAlarmSystemStubs AlarmSystemStubs ACSJMSMessageEntityStubs acsnc laserSourceAcsSpecific

# <brief description of xxxxx program>
testDriver_OBJECTS   = testDriver
testDriver_LIBS      = AlarmTestMountImpl testCppAlarmSourceComponentsStubs maciClient AcsAlarmSystemStubs AlarmSystemStubs ACSJMSMessageEntityStubs acsnc laserSourceAcsSpecific

testXML_OBJECTS = acsalarmDOMErrorHandler testXML
testXML_LIBS    = acsErrTypeAlarmSourceFactory cdb cppunit logging acsAlSysSource acsXercesUtilities maciErrType acscommonStubs laserSourceAcsSpecific

testXML_2_OBJECTS = acsalarmDOMErrorHandler testXML_2
testXML_2_LIBS    = acsErrTypeAlarmSourceFactory cdb cppunit logging acsAlSysSource acsXercesUtilities maciErrType acscommonStubs laserSourceAcsSpecific
#
# special compilation flags for single c sources
#yyyyy_CFLAGS   = 

#
# Includes (.h) files (public only)
# ---------------------------------
# INCLUDES        = 

#
# Libraries (public and local)
# ----------------------------
LIBRARIES       = 
LIBRARIES_L     = AlarmTestMountImpl AlarmTestMountMultiThreadedImpl

# <brief description of alsysTestMountImpl library>
AlarmTestMountImpl_OBJECTS  = AlarmTestMountImpl
AlarmTestMountImpl_LIBS		= testCppAlarmSourceComponentsStubs acsAlSysSource acsErrTypeAlarmSourceFactory maciErrType acscomponent archiveevents

# <brief description of alsysTestMountImpl library>
AlarmTestMountMultiThreadedImpl_OBJECTS  = AlarmTestMountMultiThreadedImpl
AlarmTestMountMultiThreadedImpl_LIBS		= testCppAlarmSourceComponentsStubs acsAlSysSource acsErrTypeAlarmSourceFactory maciErrType acscomponent archiveevents

#
# Scripts (public and local)
# ----------------------------
SCRIPTS         =
SCRIPTS_L       = alarmTestPrologue alarmTATEnv alarmTestEpilogue

#
# TCL scripts (public and local)
# ------------------------------
TCL_SCRIPTS     =
TCL_SCRIPTS_L   =

#
# Python stuff (public and local)
# ----------------------------
PY_SCRIPTS         =
PY_SCRIPTS_L       =

PY_MODULES         =
PY_MODULES_L       =

PY_PACKAGES        =
PY_PACKAGES_L      =
pppppp_MODULES	   =

#
# <brief description of tttttt tcl-script>
tttttt_OBJECTS  =
tttttt_TCLSH    = 
tttttt_LIBS     = 

#
# TCL libraries (public and local)
# ------------------------------
TCL_LIBRARIES   =
TCL_LIBRARIES_L =

#
# <brief description of tttlll library>
tttlll_OBJECTS  = 

#
# Configuration Database Files
# ----------------------------
CDB_SCHEMAS = 

# 
# IDL Files and flags
# 
IDL_FILES = testCppAlarmSourceComponents
IDL_TAO_FLAGS =
USER_IDL =
testCppAlarmSourceComponentsStubs_LIBS = acscomponentStubs
#
# Jarfiles and their directories
#
JARFILES= 
jjj_DIRS=
jjj_EXTRAS= 
#
# java sources in Jarfile on/off
DEBUG= 
#
# ACS XmlIdl generation on/off
#
XML_IDL= 
#
# Java Component Helper Classes generation on/off
#
COMPONENT_HELPERS=
#
# Java Entity Classes generation on/off
#
XSDBIND=
#
# Schema Config files for the above
#
XSDBIND_INCLUDE=
# man pages to be done
# --------------------
MANSECTIONS =
MAN1 =
MAN3 =
MAN5 =
MAN7 =
MAN8 =

#
# local man pages
# ---------------
MANl =

#
# ASCII file to be converted into Framemaker-MIF
# --------------------
ASCII_TO_MIF = 

#
# other files to be installed
#----------------------------
INSTALL_FILES =

#
# list of all possible C-sources (used to create automatic dependencies)
# ------------------------------
CSOURCENAMES = \
	$(foreach exe, $(EXECUTABLES) $(EXECUTABLES_L), $($(exe)_OBJECTS)) \
	$(foreach rtos, $(RTAI_MODULES) , $($(rtos)_OBJECTS)) \
	$(foreach lib, $(LIBRARIES) $(LIBRARIES_L), $($(lib)_OBJECTS))

#
#>>>>> END OF standard rules

#
# INCLUDE STANDARDS
# -----------------

MAKEDIRTMP := $(shell searchFile include/acsMakefile)
ifneq ($(MAKEDIRTMP),\#error\#)
   MAKEDIR := $(MAKEDIRTMP)/include
   include $(MAKEDIR)/acsMakefile
endif

#
# TARGETS
# -------
all:	do_all
	@mkdir -p tmp
	@echo " . . . 'all' done" 

clean : clean_all 
	$(RM) sed.scan
	$(RM) AlarmSystemConfiguration.xml
	$(RM) logs.xml
	$(RM) tmp tatlogs
	@echo " . . . clean done"

clean_dist : clean_all clean_dist_all 
	@echo " . . . clean_dist done"

man   : do_man 
	@echo " . . . man page(s) done"

install : install_all
	@echo " . . . installation done"


#___oOo___
