/*******************************************************************************
* ALMA - Atacama Large Millimiter Array
* (c) European Southern Observatory, 2009
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the GNU Lesser General Public
* License as published by the Free Software Foundation; either
* version 2.1 of the License, or (at your option) any later version.
*
* This library is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
* Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public
* License along with this library; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  USA
*
* "@(#) $Id: MonitorComponent.cpp,v 1.3 2011/04/28 02:14:13 tstaig Exp $"
*
* who       when      what
* --------  --------  ----------------------------------------------
* bjeram  2009-02-11  created
*/

#include "vltPort.h"

static char *rcsId="@(#) $Id: MonitorComponent.cpp,v 1.3 2011/04/28 02:14:13 tstaig Exp $";
static void *use_rcsId = ((void)&use_rcsId,(void *) &rcsId);

#include "MonitorComponent.h"
#include "MonitorCollectorErr.h"

using namespace TMCDB;
using namespace MonitorCollectorErr;


MonitorComponent::MonitorComponent(ACS::CharacteristicComponent_ptr comp, maci::ContainerServices *cs)
: component_m(comp),
  seqIndex_m(0),
  containerServices_m(cs),
  monitoring_m(false)
  {
	AUTO_TRACE("MonitorComponent::MonitorComponent");

	compDesc_m = component_m->descriptor();
	numOfProp_m = compDesc_m->properties.length();

	monitorDataBlock_m.componentName = comp->name(); //CORBA::string_dup(comp->name());
	monitorDataBlock_m.startTime = monitorDataBlock_m.stopTime = 0;
  }//MonitorComponent


MonitorComponent::~MonitorComponent()
{
	AUTO_TRACE("MonitorComponent::~MonitorComponent");
	unsigned int numOfProp = monitorPoints_m.size();

	for( unsigned int i=0; i<numOfProp; i++ )
	{
		monitorPoints_m[i]->stopMonitoring();
		containerServices_m->deactivateOffShoot(monitorPoints_m[i]);
	}
}//~MonitorComponent


void MonitorComponent::setDeviceSerialNumber(serialNumberType sn)
{
	AUTO_TRACE("MonitorComponent::setDeviceSerialNumber");
	ACE_Guard<ACE_Thread_Mutex>   prot(m_proMutex);
	monitorDataBlock_m.deviceSerialNumber = CORBA::string_dup(sn);

	ACS_LOG(LM_FULL_INFO ,"MonitorComponent::setDeviceSerialNumber", (LM_DEBUG, "set serial number for the device %s to %s.",
			monitorDataBlock_m.componentName.in(), monitorDataBlock_m.deviceSerialNumber.in()));
}//setSerialNumber

void MonitorComponent::setPropertySerialNumber(char* propertyName, serialNumberTypeSeq sn)
{
	AUTO_TRACE("MonitorComponent::setDeviceSerialNumber");

	ACE_Guard<ACE_Thread_Mutex>   prot(m_proMutex);

	unsigned int numOfProp = monitorPoints_m.size();

		for( unsigned int i=0; i<numOfProp; i++ )
		{
			if ( monitorPoints_m[i]->getPropertyName().find(propertyName) != ACE_CString::npos )
			{
				monitorPoints_m[i]->setPropertySerialNumber(sn);

				unsigned int numOfSN = sn.length();
				ACE_CString stringSN;

				for( unsigned int j=0; j<numOfSN; j++ )
				{
					stringSN += "[";
					stringSN += sn[j];
					stringSN += "]";
				}
				ACS_LOG(LM_FULL_INFO ,"MonitorComponent::setPropertySerialNumber", (LM_DEBUG, "set serial number(s) for property %s: %s.",
											     propertyName, stringSN.c_str()));
				return;
			}
		}

		//if we go out of the loop w/o finding the property we have to throw an exception
		NonExsistentPropertyExImpl ex(__FILE__, __LINE__, "MonitorComponent::setPropertySerialNumber");
		ex.setProperty(propertyName);

		throw ex;
}//setPropertiesSerialNumber


ACS::TimeInterval MonitorComponent::propertyArchivingInterval(ACS::PropertyDesc *propertyDesc)
{
	ACS::Property *property=propertyDesc->property_ref;
	CORBA::Any  *anyCharacteristic;
	char *strCharacteristic;
	double archiveMaxInt=0.0, minTimerTrigger=0.0;


	try
	{
		anyCharacteristic = property->get_characteristic_by_name("archive_mechanism");
		*anyCharacteristic >>= CORBA::Any::to_string(strCharacteristic, 0);
		if ( strcmp(strCharacteristic, "monitor_collector")!=0 )
		{
			ACS_LOG(LM_FULL_INFO ,"MonitorComponent::propertyArchivingInterval", (LM_DEBUG, "Values from property %s (%s) will NOT be collected, because archive_mechanism is NOT set to 'monitor_collector', but to: %s.",
					propertyDesc->name.in(),
					property->_repository_id(),
					strCharacteristic
			));
			return 0;
		}//if


		anyCharacteristic = property->get_characteristic_by_name("archive_max_int");
		*anyCharacteristic >>= CORBA::Any::to_string(strCharacteristic, 0);
		std::istringstream i(strCharacteristic);
		i >> archiveMaxInt;
		archiveMaxInt *= static_cast<double>(10000000.0); //we have to convert to 100s nsec.

		anyCharacteristic = property->get_characteristic_by_name("min_timer_trig");
		*anyCharacteristic >>= CORBA::Any::to_string(strCharacteristic, 0);
		std::istringstream i1(strCharacteristic);
		i1 >> minTimerTrigger;
		minTimerTrigger *= static_cast<double>(10000000.0); //we have to convert to 100s nsec.
		if ( archiveMaxInt< minTimerTrigger ) //we can not get values faster than minTimmerTrigger
		{
			ACS_LOG(LM_FULL_INFO ,"MonitorComponent::propertyArchivingInterval",
								(LM_WARNING, "Because archive_max_int (%f) is smaller than min_timer_trig(%f), the values of property %s (%s) will be collected with time trigger: %f .",
								archiveMaxInt,
								minTimerTrigger,
								propertyDesc->name.in(),
								property->_repository_id(),
								minTimerTrigger
						));
						return static_cast<ACS::TimeInterval>(minTimerTrigger);
		}//if

	}
	catch(CORBA::SystemException &ex)
	{
		ACE_PRINT_EXCEPTION(ex, "CORBA problem in MonitorComponent::propertyArchivingInterval");
		return 0;
	}
	catch(...)
	{
		printf("problem in MonitorComponent::propertyArchivingInterval!!!\n");
		return 0;
	}//try-catch

	return static_cast<ACS::TimeInterval>(archiveMaxInt);
}//propertyArchivingInterval

bool MonitorComponent::addProperty(const char *propName)
{

	AUTO_TRACE("MonitorComponent::addProperty");

	//loop over all properties of the component for the right property
	for(unsigned int i=0; i<numOfProp_m; i++)
		{

		if (strcmp(compDesc_m->properties[i].name.in(), propName)==0)
		{
			ACE_CString  propType = compDesc_m->properties[i].property_ref->_repository_id();

			ACS::TimeInterval monitoringInterval = propertyArchivingInterval(&compDesc_m->properties[i]);
 			if ( monitoringInterval!=0 )
 			{
 				//should we check the return value ?
				return addProperty(compDesc_m->properties[i].name.in(), propType.c_str(), compDesc_m->properties[i].property_ref, monitoringInterval);
 			}//if
			break;
		}//if

		}//for
	return false;
}//addProperty

bool MonitorComponent::addProperty(const char *propName,  const char *pType,  ACS::Property* propRef, ACS::TimeInterval &monitoringInterval)
{
	AUTO_TRACE("MonitorComponent::addProperty");
	MonitorPointBase * mp=0;

	ACE_CString propType(pType);

	ACS_LOG(LM_FULL_INFO ,"MonitorComponent::addProperty", (LM_DEBUG, "Going to add property[%d] = %s (%s).",
			seqIndex_m,
			propName,
			propType.c_str()
	));

	//here we have to check for the type. We could do using _is_a(..), but it is a remote call,
	// ... or put to an any and get type out
	// here we use if but could be something else

	if (propType.find("doubleSeq:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<const ACS::doubleSeq&, TMCDB::doubleSeqBlobDataSeq, ACS::PdoubleSeq, POA_ACS::CBdoubleSeq, CORBA::Double>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::doubleSeqValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]
		);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;
	}//if

	if (propType.find("double:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<CORBA::Double, TMCDB::doubleBlobDataSeq, ACS::Pdouble, POA_ACS::CBdouble, CORBA::Double>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::doubleValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]
		);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	////////////////////
	if (propType.find("longSeq:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<const ACS::longSeq&, TMCDB::longSeqBlobDataSeq, ACS::PlongSeq, POA_ACS::CBlongSeq, CORBA::Long>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::longSeqValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]
		);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	if (propType.find("long:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<CORBA::Long, TMCDB::longBlobDataSeq, ACS::Plong, POA_ACS::CBlong, CORBA::Long>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::longValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	///////////////////////
	if (propType.find("floatSeq:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<const ACS::floatSeq&, TMCDB::floatSeqBlobDataSeq, ACS::PfloatSeq, POA_ACS::CBfloatSeq, CORBA::Float>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::floatSeqValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	if (propType.find("float:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<CORBA::Float, TMCDB::floatBlobDataSeq, ACS::Pfloat, POA_ACS::CBfloat, CORBA::Float>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::floatValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	/////////////////////////////
	if (propType.find("patternSeq:")!=ACE_CString::npos)
	{
		NonSupportedTypeExImpl ex(__FILE__, __LINE__, "MonitorComponent::addProperties");
		ex.setProperty(propName);
		ex.setPropertyType(propType);
		ex.log(LM_WARNING);

		return false;
	}//if

	if (propType.find("pattern:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<ACS::pattern, TMCDB::patternBlobDataSeq, ACS::Ppattern, POA_ACS::CBpattern, ACS::pattern>(propName,
				monitoringInterval,
				propRef,
				TMCDB::patternValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if


	////////
	if (propType.find("longLongSeq:")!=ACE_CString::npos)
	{
		NonSupportedTypeExImpl ex(__FILE__, __LINE__, "MonitorComponent::addProperties");
		ex.setProperty(propName);
		ex.setPropertyType(propType);
		ex.log(LM_WARNING);

		return false;
	}//if

	if (propType.find("longLong:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<ACS::longLong, TMCDB::longLongBlobDataSeq, ACS::PlongLong, POA_ACS::CBlongLong, ACS::longLong>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::longLongValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if


	/////////
	if (propType.find("uLongLongSeq:")!=ACE_CString::npos)
	{
		NonSupportedTypeExImpl ex(__FILE__, __LINE__, "MonitorComponent::addProperties");
		ex.setProperty(propName);
		ex.setPropertyType(propType);
		ex.log(LM_WARNING);

		return false;
	}//if

	if (propType.find("uLongLong:")!=ACE_CString::npos)
	{
		mp = new MonitorPoint<ACS::uLongLong, TMCDB::uLongLongBlobDataSeq, ACS::PuLongLong, POA_ACS::CBuLongLong, ACS::uLongLong>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::uLongLongValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;
	}//if

	/////////
	if (propType.find("stringSeq:")!=ACE_CString::npos)
	{
		//TBD: could be that string/const char* needs template specialization due to corba memory management!
		mp = new MonitorPoint<const ACS::stringSeq&, TMCDB::stringSeqBlobDataSeq, ACS::PstringSeq, POA_ACS::CBstringSeq, char *>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::stringSeqValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;;
	}//if

	if (propType.find("string:")!=ACE_CString::npos)
	{
		//TBD: could be that string/const char* needs template specialization due to corba memory management!
		mp = new MonitorPoint<const char*, TMCDB::stringBlobDataSeq, ACS::Pstring, POA_ACS::CBstring, char *>(
				propName,
				monitoringInterval,
				propRef,
				TMCDB::stringValueType,
				monitorDataBlock_m.monitorBlobs[seqIndex_m]);
		mp->activate(containerServices_m);
		monitorPoints_m[seqIndex_m] = mp;
		seqIndex_m++;
		return true;
	}


	NonSupportedTypeExImpl ex(__FILE__, __LINE__, "MonitorComponent::addProperty");
	ex.setProperty(propName);
	ex.setPropertyType(propType);
	// here we just log if there is not supported type
	ex.log(LM_WARNING);
	return false;

}//addProperty

void MonitorComponent::addAllProperties()
{
	AUTO_TRACE("MonitorComponent::addAllProperties");

	ACS::TimeInterval monitoringInterval=0;

	ACE_CString propType;

	ACE_Guard<ACE_Thread_Mutex>   prot(m_proMutex);

	//set the size of the vector and sequence
	monitorPoints_m = std::vector<MonitorPointBase*>(numOfProp_m);

	monitorDataBlock_m.monitorBlobs.length(numOfProp_m);

	//let's loop over the properties
	for(unsigned int i=0; i<numOfProp_m; i++)
	{
		propType = compDesc_m->properties[i].property_ref->_repository_id();

		monitoringInterval = propertyArchivingInterval(&compDesc_m->properties[i]);
 		if ( monitoringInterval!=0 )
 		{
 			//should we check the return value ?
 			addProperty(compDesc_m->properties[i].name.in(), propType.c_str(), compDesc_m->properties[i].property_ref, monitoringInterval);
 		}//if
	}//for

	// do we have to readjust the size ?
	if (monitorPoints_m.size()!= seqIndex_m)
	{
		//printf("resized\n");
		monitorPoints_m.resize(seqIndex_m);
		monitorDataBlock_m.monitorBlobs.length(seqIndex_m);
	}//if

}//addAllProperties

void MonitorComponent::startMonitoring()
{
	AUTO_TRACE("MonitorComponent::startMonitoring");
	unsigned int numOfProp = monitorPoints_m.size();

	for( unsigned int i=0; i<numOfProp; i++ )
		monitorPoints_m[i]->startMonitoring();
	monitoring_m = true;

	m_monitoringStartTime = getTimeStamp();

	// here we set start and stop time to the same value so that can later use stopTime to set startTime in fillSeq
	monitorDataBlock_m.startTime = monitorDataBlock_m.stopTime = getTimeStamp();
}//startMonitoring

void MonitorComponent::stopMonitoring()
{
	AUTO_TRACE("MonitorComponent::stopMonitoring");
	unsigned int numOfProp = monitorPoints_m.size();

	for( unsigned int i=0; i<numOfProp; i++ )
		monitorPoints_m[i]->stopMonitoring();

	monitoring_m = false;

	// here we have to set proper start and stop time
	//monitorDataBlock_m.startTime = monitorDataBlock_m.stopTime;
	monitorDataBlock_m.startTime = m_monitoringStartTime;
	monitorDataBlock_m.stopTime = getTimeStamp();
}//stopMonitoring


void MonitorComponent::fillSeq()
{
	ACE_Guard<ACE_Thread_Mutex>   prot(m_proMutex);
	unsigned int numOfProp = monitorPoints_m.size();


	if (monitoring_m)
	{
		monitorDataBlock_m.startTime = m_monitoringStartTime;
		m_monitoringStartTime = getTimeStamp();
	}

	for( unsigned int i=0; i<numOfProp; i++ )
		monitorPoints_m[i]->fillSeq();

	if (monitoring_m)
	{
//		monitorDataBlock_m.startTime = monitorDataBlock_m.stopTime;
		monitorDataBlock_m.stopTime = getTimeStamp();
	}//if
}//fillSeq


void MonitorComponent::set_archiving_interval(const char* propertyName, ACS::TimeInterval time)
{
	AUTO_TRACE("MonitorComponent::set_archiving_interval");
	unsigned int numOfProp = monitorPoints_m.size();
	ACE_CString prop(ACE_CString(component_m->name())+ACE_CString(":")+ACE_CString(propertyName));

	for( unsigned int i=0; i<numOfProp; i++ )
		if(strcmp(monitorPoints_m[i]->getPropertyName().c_str(), prop.c_str())==0)
			monitorPoints_m[i]->set_archiving_interval(time);
}

void MonitorComponent::suppress_archiving(const char* propertyName)
{
	AUTO_TRACE("MonitorComponent::supress_archiving");
	unsigned int numOfProp = monitorPoints_m.size();
	ACE_CString prop(ACE_CString(component_m->name())+ACE_CString(":")+ACE_CString(propertyName));

	for( unsigned int i=0; i<numOfProp; i++ ) {
		if(strcmp(monitorPoints_m[i]->getPropertyName().c_str(), prop.c_str())==0)
			monitorPoints_m[i]->suppress_archiving();
	}
}

void MonitorComponent::enable_archiving(const char* propertyName)
{
	AUTO_TRACE("MonitorComponent::enable_archiving");
	unsigned int numOfProp = monitorPoints_m.size();
	ACE_CString prop(ACE_CString(component_m->name())+ACE_CString(":")+ACE_CString(propertyName));

	for( unsigned int i=0; i<numOfProp; i++ )
		if(strcmp(monitorPoints_m[i]->getPropertyName().c_str(), prop.c_str())==0)
			monitorPoints_m[i]->enable_archiving();
}

/*___oOo___*/
