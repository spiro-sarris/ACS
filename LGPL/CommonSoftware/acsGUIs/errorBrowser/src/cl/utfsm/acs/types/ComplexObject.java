/**
 * @author Mauricio Araya (maray[at]inf.utfsm.cl)
 * @author Jorge Avarias (javarias[at]alumnos.inf.utfsm.cl)
 */

package cl.utfsm.acs.types;
import java.util.ArrayList;
import java.util.Hashtable;


/** A complex object is a TypedObject that implements AcsComplexType definitions.
 * This means, that has attributes defined in the AcsComplexType implemented here as
 * hashtables. Why hashtables?, that is a good question, maybe an Arraylist is enought,
 * but currently ErrorBrowserEditor application use hashtables for "historical" reasons.
 * @author Mauricio Araya (maray[at]inf.utfsm.cl)
 */
public class ComplexObject extends TypedObject {
        @SuppressWarnings("hiding")
        /** The complex type. */
        protected AcsComplexType type;
        /** The attribute hashtable, that containes SimpleObjects */
        protected Hashtable<String,SimpleObject> attributes;
        /** Setup the type, and with it creates the hashtable entries.
         * @param type A complex type
         */
        public ComplexObject(AcsComplexType type){
                if (type==null)
                        throw new NullPointerException();
                this.type=type;
                attributes=new Hashtable<String,SimpleObject>();
                ArrayList<String> names = type.getAttrNames();
                for (String n : names){
                        SimpleObject simple=new SimpleObject(type.getAttrType(n));
                        simple.setValue("");
                        attributes.put(n,simple);
                }
        }
        /** Set an attribute value, by name.
         * @param name the name of the attribute to setup.
         * @param value the string value to setup.
         */
        public void setAttributeValue(String name,String value){
                for (String k: attributes.keySet())
                        if (k.compareTo(name)==0){
                                SimpleObject o=attributes.get(name);
                                o.setValue(value);
                                return;
                        }
                throw new java.lang.IllegalArgumentException("The attribute \""+name+"\" is not supported by \""+type.name+"\" type definition.");
        }
        /** Get directly the value of a given attribute.
         * @param name the attribute name
         * @return the string value of the attribute, or else null.
         */
        public String getAttributeValue(String name){
        	SimpleObject ob=attributes.get(name);
        	if (ob==null) return null;
        	return(ob.getValue());
        }
        /** Get an attribute object by name.
         * @param name the attribute name
         * @return the AcsAttribute object.
         */
        public SimpleObject getAttribute(String name){
        	return(attributes.get(name));
        }
        /** Return the attributes hashtable.
         * @return the attributes hashtable.
         */
        public Hashtable<String,SimpleObject> getAttributes(){
                return(attributes);
        }
}


