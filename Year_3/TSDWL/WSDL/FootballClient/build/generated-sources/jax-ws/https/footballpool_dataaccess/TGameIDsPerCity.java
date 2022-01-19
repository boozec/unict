
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tGameIDsPerCity complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tGameIDsPerCity">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="sCity" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iGameIDs" type="{https://footballpool.dataaccess.eu}ArrayOfInt"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tGameIDsPerCity", propOrder = {
    "sCity",
    "iGameIDs"
})
public class TGameIDsPerCity {

    @XmlElement(required = true)
    protected String sCity;
    @XmlElement(required = true)
    protected ArrayOfInt iGameIDs;

    /**
     * Gets the value of the sCity property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSCity() {
        return sCity;
    }

    /**
     * Sets the value of the sCity property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSCity(String value) {
        this.sCity = value;
    }

    /**
     * Gets the value of the iGameIDs property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOfInt }
     *     
     */
    public ArrayOfInt getIGameIDs() {
        return iGameIDs;
    }

    /**
     * Sets the value of the iGameIDs property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOfInt }
     *     
     */
    public void setIGameIDs(ArrayOfInt value) {
        this.iGameIDs = value;
    }

}
