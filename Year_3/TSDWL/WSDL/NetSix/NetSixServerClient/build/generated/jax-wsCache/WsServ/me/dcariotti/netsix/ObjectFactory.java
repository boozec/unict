
package me.dcariotti.netsix;

import javax.xml.bind.JAXBElement;
import javax.xml.bind.annotation.XmlElementDecl;
import javax.xml.bind.annotation.XmlRegistry;
import javax.xml.namespace.QName;


/**
 * This object contains factory methods for each 
 * Java content interface and Java element interface 
 * generated in the me.dcariotti.netsix package. 
 * <p>An ObjectFactory allows you to programatically 
 * construct new instances of the Java representation 
 * for XML content. The Java representation of XML 
 * content can consist of schema derived interfaces 
 * and classes representing the binding of schema 
 * type definitions, element declarations and model 
 * groups.  Factory methods for each of these are 
 * provided in this class.
 * 
 */
@XmlRegistry
public class ObjectFactory {

    private final static QName _Richiedi_QNAME = new QName("http://wsserv.dcariotti.me/", "richiedi");
    private final static QName _RichiediResponse_QNAME = new QName("http://wsserv.dcariotti.me/", "richiediResponse");

    /**
     * Create a new ObjectFactory that can be used to create new instances of schema derived classes for package: me.dcariotti.netsix
     * 
     */
    public ObjectFactory() {
    }

    /**
     * Create an instance of {@link Richiedi }
     * 
     */
    public Richiedi createRichiedi() {
        return new Richiedi();
    }

    /**
     * Create an instance of {@link RichiediResponse }
     * 
     */
    public RichiediResponse createRichiediResponse() {
        return new RichiediResponse();
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link Richiedi }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://wsserv.dcariotti.me/", name = "richiedi")
    public JAXBElement<Richiedi> createRichiedi(Richiedi value) {
        return new JAXBElement<Richiedi>(_Richiedi_QNAME, Richiedi.class, null, value);
    }

    /**
     * Create an instance of {@link JAXBElement }{@code <}{@link RichiediResponse }{@code >}}
     * 
     */
    @XmlElementDecl(namespace = "http://wsserv.dcariotti.me/", name = "richiediResponse")
    public JAXBElement<RichiediResponse> createRichiediResponse(RichiediResponse value) {
        return new JAXBElement<RichiediResponse>(_RichiediResponse_QNAME, RichiediResponse.class, null, value);
    }

}
