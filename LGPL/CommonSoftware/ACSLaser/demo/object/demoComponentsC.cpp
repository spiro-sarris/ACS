// -*- C++ -*-
// $Id$

/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v1.8.1
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 *       http://www.cs.wustl.edu/~schmidt/doc-center.html
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       http://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     http://www.cs.wustl.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// be/be_codegen.cpp:426


#include "demoComponentsC.h"
#include "tao/AnyTypeCode/Null_RefCount_Policy.h"
#include "tao/AnyTypeCode/TypeCode_Constants.h"
#include "tao/AnyTypeCode/Alias_TypeCode_Static.h"
#include "tao/AnyTypeCode/Objref_TypeCode_Static.h"
#include "tao/AnyTypeCode/String_TypeCode_Static.h"
#include "tao/CDR.h"
#include "tao/Exception_Data.h"
#include "tao/Invocation_Adapter.h"
#include "tao/Object_T.h"
#include "tao/CDR.h"
#include "tao/AnyTypeCode/Any.h"
#include "tao/AnyTypeCode/Any_Impl_T.h"
#include "tao/Basic_Arguments.h"
#include "ace/OS_NS_string.h"

#if !defined (__ACE_INLINE__)
#include "demoComponentsC.inl"
#endif /* !defined INLINE */

// TAO_IDL - Generated from
// be/be_visitor_arg_traits.cpp:68

TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/interface_cs.cpp:51

// Traits specializations for alarmsystemdemo::PS.

alarmsystemdemo::PS_ptr
TAO::Objref_Traits<alarmsystemdemo::PS>::duplicate (
    alarmsystemdemo::PS_ptr p)
{
  return alarmsystemdemo::PS::_duplicate (p);
}

void
TAO::Objref_Traits<alarmsystemdemo::PS>::release (
    alarmsystemdemo::PS_ptr p)
{
  ::CORBA::release (p);
}

alarmsystemdemo::PS_ptr
TAO::Objref_Traits<alarmsystemdemo::PS>::nil (void)
{
  return alarmsystemdemo::PS::_nil ();
}

::CORBA::Boolean
TAO::Objref_Traits<alarmsystemdemo::PS>::marshal (
    const alarmsystemdemo::PS_ptr p,
    TAO_OutputCDR & cdr)
{
  return ::CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer) (
    ::CORBA::Object_ptr obj) = 0;

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::PS::faultPS (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_PS_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_PS_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "faultPS",
      7,
      this->the_TAO_PS_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::PS::terminate_faultPS (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_PS_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_PS_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "terminate_faultPS",
      17,
      this->the_TAO_PS_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

alarmsystemdemo::PS::PS (void)
 : the_TAO_PS_Proxy_Broker_ (0)
{
  this->alarmsystemdemo_PS_setup_collocation ();
}

void
alarmsystemdemo::PS::alarmsystemdemo_PS_setup_collocation ()
{
  if (::alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer)
    {
      this->the_TAO_PS_Proxy_Broker_ =
        ::alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer (this);
    }
  
  this->ACS_ACSComponent_setup_collocation ();
}

alarmsystemdemo::PS::~PS (void)
{}

void 
alarmsystemdemo::PS::_tao_any_destructor (void *_tao_void_pointer)
{
  PS *_tao_tmp_pointer =
    static_cast<PS *> (_tao_void_pointer);
  ::CORBA::release (_tao_tmp_pointer);
}

alarmsystemdemo::PS_ptr
alarmsystemdemo::PS::_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<PS>::narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/PS:1.0",
        alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::PS_ptr
alarmsystemdemo::PS::_unchecked_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<PS>::unchecked_narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/PS:1.0",
        alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::PS_ptr
alarmsystemdemo::PS::_duplicate (PS_ptr obj)
{
  if (! ::CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
alarmsystemdemo::PS::_tao_release (PS_ptr obj)
{
  ::CORBA::release (obj);
}

::CORBA::Boolean
alarmsystemdemo::PS::_is_a (const char *value)
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:alma/ACS/ACSComponent:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:alma/alarmsystemdemo/PS:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return this->::CORBA::Object::_is_a (value);
    }
}

const char* alarmsystemdemo::PS::_interface_repository_id (void) const
{
  return "IDL:alma/alarmsystemdemo/PS:1.0";
}

::CORBA::Boolean
alarmsystemdemo::PS::marshal (TAO_OutputCDR &cdr)
{
  return (cdr << this);
}

// TAO_IDL - Generated from
// be/be_visitor_typecode/objref_typecode.cpp:76

static TAO::TypeCode::Objref<char const *,
                             TAO::Null_RefCount_Policy>
  _tao_tc_alarmsystemdemo_PS (
    ::CORBA::tk_objref,
    "IDL:alma/alarmsystemdemo/PS:1.0",
    "PS");
  

namespace alarmsystemdemo
{
  ::CORBA::TypeCode_ptr const _tc_PS =
    &_tao_tc_alarmsystemdemo_PS;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_cs.cpp:51

// Traits specializations for alarmsystemdemo::Mount.

alarmsystemdemo::Mount_ptr
TAO::Objref_Traits<alarmsystemdemo::Mount>::duplicate (
    alarmsystemdemo::Mount_ptr p)
{
  return alarmsystemdemo::Mount::_duplicate (p);
}

void
TAO::Objref_Traits<alarmsystemdemo::Mount>::release (
    alarmsystemdemo::Mount_ptr p)
{
  ::CORBA::release (p);
}

alarmsystemdemo::Mount_ptr
TAO::Objref_Traits<alarmsystemdemo::Mount>::nil (void)
{
  return alarmsystemdemo::Mount::_nil ();
}

::CORBA::Boolean
TAO::Objref_Traits<alarmsystemdemo::Mount>::marshal (
    const alarmsystemdemo::Mount_ptr p,
    TAO_OutputCDR & cdr)
{
  return ::CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer) (
    ::CORBA::Object_ptr obj) = 0;

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::Mount::faultMount (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_Mount_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_Mount_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "faultMount",
      10,
      this->the_TAO_Mount_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::Mount::terminate_faultMount (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_Mount_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_Mount_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "terminate_faultMount",
      20,
      this->the_TAO_Mount_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

alarmsystemdemo::Mount::Mount (void)
 : the_TAO_Mount_Proxy_Broker_ (0)
{
  this->alarmsystemdemo_Mount_setup_collocation ();
}

void
alarmsystemdemo::Mount::alarmsystemdemo_Mount_setup_collocation ()
{
  if (::alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer)
    {
      this->the_TAO_Mount_Proxy_Broker_ =
        ::alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer (this);
    }
  
  this->ACS_ACSComponent_setup_collocation ();
}

alarmsystemdemo::Mount::~Mount (void)
{}

void 
alarmsystemdemo::Mount::_tao_any_destructor (void *_tao_void_pointer)
{
  Mount *_tao_tmp_pointer =
    static_cast<Mount *> (_tao_void_pointer);
  ::CORBA::release (_tao_tmp_pointer);
}

alarmsystemdemo::Mount_ptr
alarmsystemdemo::Mount::_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<Mount>::narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/Mount:1.0",
        alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::Mount_ptr
alarmsystemdemo::Mount::_unchecked_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<Mount>::unchecked_narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/Mount:1.0",
        alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::Mount_ptr
alarmsystemdemo::Mount::_duplicate (Mount_ptr obj)
{
  if (! ::CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
alarmsystemdemo::Mount::_tao_release (Mount_ptr obj)
{
  ::CORBA::release (obj);
}

::CORBA::Boolean
alarmsystemdemo::Mount::_is_a (const char *value)
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:alma/ACS/ACSComponent:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:alma/alarmsystemdemo/Mount:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return this->::CORBA::Object::_is_a (value);
    }
}

const char* alarmsystemdemo::Mount::_interface_repository_id (void) const
{
  return "IDL:alma/alarmsystemdemo/Mount:1.0";
}

::CORBA::Boolean
alarmsystemdemo::Mount::marshal (TAO_OutputCDR &cdr)
{
  return (cdr << this);
}

// TAO_IDL - Generated from
// be/be_visitor_typecode/objref_typecode.cpp:76

static TAO::TypeCode::Objref<char const *,
                             TAO::Null_RefCount_Policy>
  _tao_tc_alarmsystemdemo_Mount (
    ::CORBA::tk_objref,
    "IDL:alma/alarmsystemdemo/Mount:1.0",
    "Mount");
  

namespace alarmsystemdemo
{
  ::CORBA::TypeCode_ptr const _tc_Mount =
    &_tao_tc_alarmsystemdemo_Mount;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_cs.cpp:51

// Traits specializations for alarmsystemdemo::Antenna.

alarmsystemdemo::Antenna_ptr
TAO::Objref_Traits<alarmsystemdemo::Antenna>::duplicate (
    alarmsystemdemo::Antenna_ptr p)
{
  return alarmsystemdemo::Antenna::_duplicate (p);
}

void
TAO::Objref_Traits<alarmsystemdemo::Antenna>::release (
    alarmsystemdemo::Antenna_ptr p)
{
  ::CORBA::release (p);
}

alarmsystemdemo::Antenna_ptr
TAO::Objref_Traits<alarmsystemdemo::Antenna>::nil (void)
{
  return alarmsystemdemo::Antenna::_nil ();
}

::CORBA::Boolean
TAO::Objref_Traits<alarmsystemdemo::Antenna>::marshal (
    const alarmsystemdemo::Antenna_ptr p,
    TAO_OutputCDR & cdr)
{
  return ::CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer) (
    ::CORBA::Object_ptr obj) = 0;

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::Antenna::faultAntenna (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_Antenna_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_Antenna_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "faultAntenna",
      12,
      this->the_TAO_Antenna_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::Antenna::terminate_faultAntenna (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_Antenna_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_Antenna_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "terminate_faultAntenna",
      22,
      this->the_TAO_Antenna_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

alarmsystemdemo::Antenna::Antenna (void)
 : the_TAO_Antenna_Proxy_Broker_ (0)
{
  this->alarmsystemdemo_Antenna_setup_collocation ();
}

void
alarmsystemdemo::Antenna::alarmsystemdemo_Antenna_setup_collocation ()
{
  if (::alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer)
    {
      this->the_TAO_Antenna_Proxy_Broker_ =
        ::alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer (this);
    }
  
  this->ACS_ACSComponent_setup_collocation ();
}

alarmsystemdemo::Antenna::~Antenna (void)
{}

void 
alarmsystemdemo::Antenna::_tao_any_destructor (void *_tao_void_pointer)
{
  Antenna *_tao_tmp_pointer =
    static_cast<Antenna *> (_tao_void_pointer);
  ::CORBA::release (_tao_tmp_pointer);
}

alarmsystemdemo::Antenna_ptr
alarmsystemdemo::Antenna::_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<Antenna>::narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/Antenna:1.0",
        alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::Antenna_ptr
alarmsystemdemo::Antenna::_unchecked_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<Antenna>::unchecked_narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/Antenna:1.0",
        alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::Antenna_ptr
alarmsystemdemo::Antenna::_duplicate (Antenna_ptr obj)
{
  if (! ::CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
alarmsystemdemo::Antenna::_tao_release (Antenna_ptr obj)
{
  ::CORBA::release (obj);
}

::CORBA::Boolean
alarmsystemdemo::Antenna::_is_a (const char *value)
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:alma/ACS/ACSComponent:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:alma/alarmsystemdemo/Antenna:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return this->::CORBA::Object::_is_a (value);
    }
}

const char* alarmsystemdemo::Antenna::_interface_repository_id (void) const
{
  return "IDL:alma/alarmsystemdemo/Antenna:1.0";
}

::CORBA::Boolean
alarmsystemdemo::Antenna::marshal (TAO_OutputCDR &cdr)
{
  return (cdr << this);
}

// TAO_IDL - Generated from
// be/be_visitor_typecode/objref_typecode.cpp:76

static TAO::TypeCode::Objref<char const *,
                             TAO::Null_RefCount_Policy>
  _tao_tc_alarmsystemdemo_Antenna (
    ::CORBA::tk_objref,
    "IDL:alma/alarmsystemdemo/Antenna:1.0",
    "Antenna");
  

namespace alarmsystemdemo
{
  ::CORBA::TypeCode_ptr const _tc_Antenna =
    &_tao_tc_alarmsystemdemo_Antenna;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_cs.cpp:51

// Traits specializations for alarmsystemdemo::MF.

alarmsystemdemo::MF_ptr
TAO::Objref_Traits<alarmsystemdemo::MF>::duplicate (
    alarmsystemdemo::MF_ptr p)
{
  return alarmsystemdemo::MF::_duplicate (p);
}

void
TAO::Objref_Traits<alarmsystemdemo::MF>::release (
    alarmsystemdemo::MF_ptr p)
{
  ::CORBA::release (p);
}

alarmsystemdemo::MF_ptr
TAO::Objref_Traits<alarmsystemdemo::MF>::nil (void)
{
  return alarmsystemdemo::MF::_nil ();
}

::CORBA::Boolean
TAO::Objref_Traits<alarmsystemdemo::MF>::marshal (
    const alarmsystemdemo::MF_ptr p,
    TAO_OutputCDR & cdr)
{
  return ::CORBA::Object::marshal (p, cdr);
}

// Function pointer for collocation factory initialization.
TAO::Collocation_Proxy_Broker * 
(*alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer) (
    ::CORBA::Object_ptr obj) = 0;

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::MF::multiFault (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_MF_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_MF_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "multiFault",
      10,
      this->the_TAO_MF_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

// TAO_IDL - Generated from
// be/be_visitor_operation/operation_cs.cpp:80

void
alarmsystemdemo::MF::terminate_multiFault (void)
{
  if (!this->is_evaluated ())
    {
      ::CORBA::Object::tao_object_initialize (this);
    }
  
  if (this->the_TAO_MF_Proxy_Broker_ == 0)
    {
      alarmsystemdemo_MF_setup_collocation ();
    }
  
  TAO::Arg_Traits< void>::ret_val _tao_retval;
  
  TAO::Argument *_the_tao_operation_signature [] =
    {
      &_tao_retval
    };
  
  TAO::Invocation_Adapter _tao_call (
      this,
      _the_tao_operation_signature,
      1,
      "terminate_multiFault",
      20,
      this->the_TAO_MF_Proxy_Broker_
    );
  
  _tao_call.invoke (0, 0);
}

alarmsystemdemo::MF::MF (void)
 : the_TAO_MF_Proxy_Broker_ (0)
{
  this->alarmsystemdemo_MF_setup_collocation ();
}

void
alarmsystemdemo::MF::alarmsystemdemo_MF_setup_collocation ()
{
  if (::alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer)
    {
      this->the_TAO_MF_Proxy_Broker_ =
        ::alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer (this);
    }
  
  this->ACS_ACSComponent_setup_collocation ();
}

alarmsystemdemo::MF::~MF (void)
{}

void 
alarmsystemdemo::MF::_tao_any_destructor (void *_tao_void_pointer)
{
  MF *_tao_tmp_pointer =
    static_cast<MF *> (_tao_void_pointer);
  ::CORBA::release (_tao_tmp_pointer);
}

alarmsystemdemo::MF_ptr
alarmsystemdemo::MF::_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<MF>::narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/MF:1.0",
        alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::MF_ptr
alarmsystemdemo::MF::_unchecked_narrow (
    ::CORBA::Object_ptr _tao_objref)
{
  return
    TAO::Narrow_Utils<MF>::unchecked_narrow (
        _tao_objref,
        "IDL:alma/alarmsystemdemo/MF:1.0",
        alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer
      );
}

alarmsystemdemo::MF_ptr
alarmsystemdemo::MF::_duplicate (MF_ptr obj)
{
  if (! ::CORBA::is_nil (obj))
    {
      obj->_add_ref ();
    }
  
  return obj;
}

void
alarmsystemdemo::MF::_tao_release (MF_ptr obj)
{
  ::CORBA::release (obj);
}

::CORBA::Boolean
alarmsystemdemo::MF::_is_a (const char *value)
{
  if (
      !ACE_OS::strcmp (
          value,
          "IDL:alma/ACS/ACSComponent:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:alma/alarmsystemdemo/MF:1.0"
        ) ||
      !ACE_OS::strcmp (
          value,
          "IDL:omg.org/CORBA/Object:1.0"
        )
    )
    {
      return true; // success using local knowledge
    }
  else
    {
      return this->::CORBA::Object::_is_a (value);
    }
}

const char* alarmsystemdemo::MF::_interface_repository_id (void) const
{
  return "IDL:alma/alarmsystemdemo/MF:1.0";
}

::CORBA::Boolean
alarmsystemdemo::MF::marshal (TAO_OutputCDR &cdr)
{
  return (cdr << this);
}

// TAO_IDL - Generated from
// be/be_visitor_typecode/objref_typecode.cpp:76

static TAO::TypeCode::Objref<char const *,
                             TAO::Null_RefCount_Policy>
  _tao_tc_alarmsystemdemo_MF (
    ::CORBA::tk_objref,
    "IDL:alma/alarmsystemdemo/MF:1.0",
    "MF");
  

namespace alarmsystemdemo
{
  ::CORBA::TypeCode_ptr const _tc_MF =
    &_tao_tc_alarmsystemdemo_MF;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:49
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<>
  ::CORBA::Boolean
  Any_Impl_T<alarmsystemdemo::PS>::to_object (
      ::CORBA::Object_ptr &_tao_elem
    ) const
  {
    _tao_elem = ::CORBA::Object::_duplicate (this->value_);
    return true;
  }
}
TAO_END_VERSIONED_NAMESPACE_DECL



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace alarmsystemdemo
{
  
  
  /// Copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      PS_ptr _tao_elem)
  {
    PS_ptr _tao_objptr =
      PS::_duplicate (_tao_elem);
    _tao_any <<= &_tao_objptr;
  }
  
  /// Non-copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      PS_ptr *_tao_elem)
  {
    TAO::Any_Impl_T<PS>::insert (
        _tao_any,
        PS::_tao_any_destructor,
        _tc_PS,
        *_tao_elem)
  }
  
  ::CORBA::Boolean
  operator>>= (
      const ::CORBA::Any &_tao_any,
      PS_ptr &_tao_elem)
  {
    return
      TAO::Any_Impl_T<PS>::extract (
          _tao_any,
          PS::_tao_any_destructor,
          _tc_PS,
          _tao_elem)
  }
}

#else

TAO_BEGIN_VERSIONED_NAMESPACE_DECL



/// Copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::PS_ptr _tao_elem)
{
  alarmsystemdemo::PS_ptr _tao_objptr =
    alarmsystemdemo::PS::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

/// Non-copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::PS_ptr *_tao_elem)
{
  TAO::Any_Impl_T<alarmsystemdemo::PS>::insert (
      _tao_any,
      alarmsystemdemo::PS::_tao_any_destructor,
      alarmsystemdemo::_tc_PS,
      *_tao_elem);
}

::CORBA::Boolean
operator>>= (
    const ::CORBA::Any &_tao_any,
    alarmsystemdemo::PS_ptr &_tao_elem)
{
  return
    TAO::Any_Impl_T<alarmsystemdemo::PS>::extract (
        _tao_any,
        alarmsystemdemo::PS::_tao_any_destructor,
        alarmsystemdemo::_tc_PS,
        _tao_elem);
}

TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:49
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<>
  ::CORBA::Boolean
  Any_Impl_T<alarmsystemdemo::Mount>::to_object (
      ::CORBA::Object_ptr &_tao_elem
    ) const
  {
    _tao_elem = ::CORBA::Object::_duplicate (this->value_);
    return true;
  }
}
TAO_END_VERSIONED_NAMESPACE_DECL



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace alarmsystemdemo
{
  
  
  /// Copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      Mount_ptr _tao_elem)
  {
    Mount_ptr _tao_objptr =
      Mount::_duplicate (_tao_elem);
    _tao_any <<= &_tao_objptr;
  }
  
  /// Non-copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      Mount_ptr *_tao_elem)
  {
    TAO::Any_Impl_T<Mount>::insert (
        _tao_any,
        Mount::_tao_any_destructor,
        _tc_Mount,
        *_tao_elem)
  }
  
  ::CORBA::Boolean
  operator>>= (
      const ::CORBA::Any &_tao_any,
      Mount_ptr &_tao_elem)
  {
    return
      TAO::Any_Impl_T<Mount>::extract (
          _tao_any,
          Mount::_tao_any_destructor,
          _tc_Mount,
          _tao_elem)
  }
}

#else

TAO_BEGIN_VERSIONED_NAMESPACE_DECL



/// Copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::Mount_ptr _tao_elem)
{
  alarmsystemdemo::Mount_ptr _tao_objptr =
    alarmsystemdemo::Mount::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

/// Non-copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::Mount_ptr *_tao_elem)
{
  TAO::Any_Impl_T<alarmsystemdemo::Mount>::insert (
      _tao_any,
      alarmsystemdemo::Mount::_tao_any_destructor,
      alarmsystemdemo::_tc_Mount,
      *_tao_elem);
}

::CORBA::Boolean
operator>>= (
    const ::CORBA::Any &_tao_any,
    alarmsystemdemo::Mount_ptr &_tao_elem)
{
  return
    TAO::Any_Impl_T<alarmsystemdemo::Mount>::extract (
        _tao_any,
        alarmsystemdemo::Mount::_tao_any_destructor,
        alarmsystemdemo::_tc_Mount,
        _tao_elem);
}

TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:49
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<>
  ::CORBA::Boolean
  Any_Impl_T<alarmsystemdemo::Antenna>::to_object (
      ::CORBA::Object_ptr &_tao_elem
    ) const
  {
    _tao_elem = ::CORBA::Object::_duplicate (this->value_);
    return true;
  }
}
TAO_END_VERSIONED_NAMESPACE_DECL



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace alarmsystemdemo
{
  
  
  /// Copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      Antenna_ptr _tao_elem)
  {
    Antenna_ptr _tao_objptr =
      Antenna::_duplicate (_tao_elem);
    _tao_any <<= &_tao_objptr;
  }
  
  /// Non-copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      Antenna_ptr *_tao_elem)
  {
    TAO::Any_Impl_T<Antenna>::insert (
        _tao_any,
        Antenna::_tao_any_destructor,
        _tc_Antenna,
        *_tao_elem)
  }
  
  ::CORBA::Boolean
  operator>>= (
      const ::CORBA::Any &_tao_any,
      Antenna_ptr &_tao_elem)
  {
    return
      TAO::Any_Impl_T<Antenna>::extract (
          _tao_any,
          Antenna::_tao_any_destructor,
          _tc_Antenna,
          _tao_elem)
  }
}

#else

TAO_BEGIN_VERSIONED_NAMESPACE_DECL



/// Copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::Antenna_ptr _tao_elem)
{
  alarmsystemdemo::Antenna_ptr _tao_objptr =
    alarmsystemdemo::Antenna::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

/// Non-copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::Antenna_ptr *_tao_elem)
{
  TAO::Any_Impl_T<alarmsystemdemo::Antenna>::insert (
      _tao_any,
      alarmsystemdemo::Antenna::_tao_any_destructor,
      alarmsystemdemo::_tc_Antenna,
      *_tao_elem);
}

::CORBA::Boolean
operator>>= (
    const ::CORBA::Any &_tao_any,
    alarmsystemdemo::Antenna_ptr &_tao_elem)
{
  return
    TAO::Any_Impl_T<alarmsystemdemo::Antenna>::extract (
        _tao_any,
        alarmsystemdemo::Antenna::_tao_any_destructor,
        alarmsystemdemo::_tc_Antenna,
        _tao_elem);
}

TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/any_op_cs.cpp:49
TAO_BEGIN_VERSIONED_NAMESPACE_DECL



namespace TAO
{
  template<>
  ::CORBA::Boolean
  Any_Impl_T<alarmsystemdemo::MF>::to_object (
      ::CORBA::Object_ptr &_tao_elem
    ) const
  {
    _tao_elem = ::CORBA::Object::_duplicate (this->value_);
    return true;
  }
}
TAO_END_VERSIONED_NAMESPACE_DECL



#if defined (ACE_ANY_OPS_USE_NAMESPACE)

namespace alarmsystemdemo
{
  
  
  /// Copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      MF_ptr _tao_elem)
  {
    MF_ptr _tao_objptr =
      MF::_duplicate (_tao_elem);
    _tao_any <<= &_tao_objptr;
  }
  
  /// Non-copying insertion.
  void
  operator<<= (
      ::CORBA::Any &_tao_any,
      MF_ptr *_tao_elem)
  {
    TAO::Any_Impl_T<MF>::insert (
        _tao_any,
        MF::_tao_any_destructor,
        _tc_MF,
        *_tao_elem)
  }
  
  ::CORBA::Boolean
  operator>>= (
      const ::CORBA::Any &_tao_any,
      MF_ptr &_tao_elem)
  {
    return
      TAO::Any_Impl_T<MF>::extract (
          _tao_any,
          MF::_tao_any_destructor,
          _tc_MF,
          _tao_elem)
  }
}

#else

TAO_BEGIN_VERSIONED_NAMESPACE_DECL



/// Copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::MF_ptr _tao_elem)
{
  alarmsystemdemo::MF_ptr _tao_objptr =
    alarmsystemdemo::MF::_duplicate (_tao_elem);
  _tao_any <<= &_tao_objptr;
}

/// Non-copying insertion.
void
operator<<= (
    ::CORBA::Any &_tao_any,
    alarmsystemdemo::MF_ptr *_tao_elem)
{
  TAO::Any_Impl_T<alarmsystemdemo::MF>::insert (
      _tao_any,
      alarmsystemdemo::MF::_tao_any_destructor,
      alarmsystemdemo::_tc_MF,
      *_tao_elem);
}

::CORBA::Boolean
operator>>= (
    const ::CORBA::Any &_tao_any,
    alarmsystemdemo::MF_ptr &_tao_elem)
{
  return
    TAO::Any_Impl_T<alarmsystemdemo::MF>::extract (
        _tao_any,
        alarmsystemdemo::MF::_tao_any_destructor,
        alarmsystemdemo::_tc_MF,
        _tao_elem);
}

TAO_END_VERSIONED_NAMESPACE_DECL



#endif

// TAO_IDL - Generated from
// be/be_visitor_interface/cdr_op_cs.cpp:54

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const alarmsystemdemo::PS_ptr _tao_objref)
{
  ::CORBA::Object_ptr _tao_corba_obj = _tao_objref;
  return (strm << _tao_corba_obj);
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    alarmsystemdemo::PS_ptr &_tao_objref)
{
  ::CORBA::Object_var obj;
  
  if (!(strm >> obj.inout ()))
    {
      return false;
    }
  
  typedef ::alarmsystemdemo::PS RHS_SCOPED_NAME;
  
  // Narrow to the right type.
  _tao_objref =
    TAO::Narrow_Utils<RHS_SCOPED_NAME>::unchecked_narrow (
        obj.in (),
        alarmsystemdemo__TAO_PS_Proxy_Broker_Factory_function_pointer
      );
    
  return true;
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/cdr_op_cs.cpp:54

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const alarmsystemdemo::Mount_ptr _tao_objref)
{
  ::CORBA::Object_ptr _tao_corba_obj = _tao_objref;
  return (strm << _tao_corba_obj);
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    alarmsystemdemo::Mount_ptr &_tao_objref)
{
  ::CORBA::Object_var obj;
  
  if (!(strm >> obj.inout ()))
    {
      return false;
    }
  
  typedef ::alarmsystemdemo::Mount RHS_SCOPED_NAME;
  
  // Narrow to the right type.
  _tao_objref =
    TAO::Narrow_Utils<RHS_SCOPED_NAME>::unchecked_narrow (
        obj.in (),
        alarmsystemdemo__TAO_Mount_Proxy_Broker_Factory_function_pointer
      );
    
  return true;
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/cdr_op_cs.cpp:54

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const alarmsystemdemo::Antenna_ptr _tao_objref)
{
  ::CORBA::Object_ptr _tao_corba_obj = _tao_objref;
  return (strm << _tao_corba_obj);
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    alarmsystemdemo::Antenna_ptr &_tao_objref)
{
  ::CORBA::Object_var obj;
  
  if (!(strm >> obj.inout ()))
    {
      return false;
    }
  
  typedef ::alarmsystemdemo::Antenna RHS_SCOPED_NAME;
  
  // Narrow to the right type.
  _tao_objref =
    TAO::Narrow_Utils<RHS_SCOPED_NAME>::unchecked_narrow (
        obj.in (),
        alarmsystemdemo__TAO_Antenna_Proxy_Broker_Factory_function_pointer
      );
    
  return true;
}

TAO_END_VERSIONED_NAMESPACE_DECL



// TAO_IDL - Generated from
// be/be_visitor_interface/cdr_op_cs.cpp:54

TAO_BEGIN_VERSIONED_NAMESPACE_DECL

::CORBA::Boolean operator<< (
    TAO_OutputCDR &strm,
    const alarmsystemdemo::MF_ptr _tao_objref)
{
  ::CORBA::Object_ptr _tao_corba_obj = _tao_objref;
  return (strm << _tao_corba_obj);
}

::CORBA::Boolean operator>> (
    TAO_InputCDR &strm,
    alarmsystemdemo::MF_ptr &_tao_objref)
{
  ::CORBA::Object_var obj;
  
  if (!(strm >> obj.inout ()))
    {
      return false;
    }
  
  typedef ::alarmsystemdemo::MF RHS_SCOPED_NAME;
  
  // Narrow to the right type.
  _tao_objref =
    TAO::Narrow_Utils<RHS_SCOPED_NAME>::unchecked_narrow (
        obj.in (),
        alarmsystemdemo__TAO_MF_Proxy_Broker_Factory_function_pointer
      );
    
  return true;
}

TAO_END_VERSIONED_NAMESPACE_DECL


