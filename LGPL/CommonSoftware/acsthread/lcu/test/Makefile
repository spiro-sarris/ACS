#*******************************************************************************
# ALMA - Atacama Large Millimiter Array
# (c) European Southern Observatory, 2006 
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
#
# "@(#) $Id: Makefile,v 1.2 2006/07/04 13:29:58 bjeram Exp $"
#
# Makefile of ........
#
# who       when      what
# --------  --------  ----------------------------------------------
# bjeram  2006-06-14  created
#

#*******************************************************************************
# This Makefile follows VLT Standards (see Makefile(5) for more).
#*******************************************************************************
# REMARKS
#    None
#------------------------------------------------------------------------
# List of files to be linked 
#!# (ICT-3855: commented out) LINK_FILES = $(foreach exe, $(EXECUTABLES_L), ../test/$(exe).cpp)
#

#
# user definable C-compilation flags
#USER_CFLAGS = 

#
# additional include and library search paths
#USER_INC = 
#USER_LIB = 

#
# MODULE CODE DESCRIPTION:
# ------------------------
# As a general rule:  public file are "cleaned" and "installed"  
#                     local (_L) are not "installed".

#
# C programs (public and local)
# -----------------------------
EXECUTABLES     =
EXECUTABLES_L   = testACSThread testACSThreadWithParameter testSelfDelThread \
                  testACSThreadStress \
                  testACSThreadStop testACSThreadTiming testACSThreadSuspend \
                  testACSThreadCorrExmpl testACSThreadNoTM \
                  testACSThreadDoubleLoop testACSThreadSleep	\
                   testACSThreadRestart testACSThreadGuard
# testACSThreadJoinable

#
# <brief description of xxxxx program>
testACSThreadWithParameter_OBJECTS = testACSThreadWithParameter

testACSThread_OBJECTS   = testACSThread	

testSelfDelThread_OBJECTS 	= testSelfDelThread

testACSThreadStress_OBJECTS 	= testACSThreadStress

testACSThreadStop_OBJECTS   = testACSThreadStop	

testACSThreadTiming_OBJECTS   = testACSThreadTiming	

testACSThreadSuspend_OBJECTS   = testACSThreadSuspend	

testACSThreadCorrExmpl_OBJECTS   = testACSThreadCorrExmpl	

testACSThreadNoTM_OBJECTS   = testACSThreadNoTM	

testACSThreadDoubleLoop_OBJECTS   = testACSThreadDoubleLoop	

testACSThreadSleep_OBJECTS   = testACSThreadSleep

testACSThreadJoinable_OBJECTS   = testACSThreadJoinable

testACSThreadRestart_OBJECTS   = testACSThreadRestart

testACSThreadGuard_OBJECTS   = testACSThreadGuard


#
# special compilation flags for single c sources
#yyyyy_CFLAGS   = 

#
# Includes (.h) files (public only)
# ---------------------------------
INCLUDES        =

#
# Libraries (public and local)
# ----------------------------
LIBRARIES       =
LIBRARIES_L     =

#
# <brief description of lllll library>
lllll_OBJECTS   =

#
# Scripts (public and local)
# ----------------------------
SCRIPTS         =
SCRIPTS_L       =

#
# TCL scripts (public and local)
# ------------------------------
TCL_SCRIPTS     =
TCL_SCRIPTS_L   =

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
# IDL Files and flags
#
IDL_FILES =
IDL_TAO_FLAGS =
USER_IDL =

#
# Configuration Database Files
# ----------------------------
CDB_SCHEMAS = 

#
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
	$(foreach lib, $(LIBRARIES) $(LIBRARIES_L), $($(lib)_OBJECTS))

#
#>>>>> END OF standard rules

#
# CHOSE PLATFORM
# --------------
# This is a LCU Makefile, so for VxVorks applications we set:
MAKE_VXWORKS = on   

ifdef WIND_BASE
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
	@echo " . . . 'all' done" 

clean : clean_all 
	@echo " . . . clean done"

clean_dist : clean_all clean_dist_all 
	@echo " . . . clean_dist done"

man   : do_man 
	@echo " . . . man page(s) done"

install : install_all
	@echo " . . . installation done"

else
all:    
	@echo " WIND_BASE not defined. Nothing to do 'all'!"
clean : 
	@echo " WIND_BASE not defined. Nothing to 'clean' !"

clean_dist : 
	@echo " WIND_BASE not defined. Nothing to 'clean_dist' !"

man   : 
	@echo " WIND_BASE not defined. Nothing to 'man' !"

install : 
	@echo " WIND_BASE not defined. Nothing to 'install' !"

endif

#___oOo___
