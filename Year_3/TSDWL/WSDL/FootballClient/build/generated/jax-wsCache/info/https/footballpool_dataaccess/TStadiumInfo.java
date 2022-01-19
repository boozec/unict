
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tStadiumInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tStadiumInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="sName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iSeatsCapacity" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sCityName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sWikipediaURL" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sGoogleMapsURL" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tStadiumInfo", propOrder = {
    "sName",
    "iSeatsCapacity",
    "sCityName",
    "sWikipediaURL",
    "sGoogleMapsURL"
})
public class TStadiumInfo {

    @XmlElement(required = true)
    protected String sName;
    protected int iSeatsCapacity;
    @XmlElement(required = true)
    protected String sCityName;
    @XmlElement(required = true)
    protected String sWikipediaURL;
    @XmlElement(required = true)
    protected String sGoogleMapsURL;

    /**
     * Gets the value of the sName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSName() {
        return sName;
    }

    /**
     * Sets the value of the sName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSName(String value) {
        this.sName = value;
    }

    /**
     * Gets the value of the iSeatsCapacity property.
     * 
     */
    public int getISeatsCapacity() {
        return iSeatsCapacity;
    }

    /**
     * Sets the value of the iSeatsCapacity property.
     * 
     */
    public void setISeatsCapacity(int value) {
        this.iSeatsCapacity = value;
    }

    /**
     * Gets the value of the sCityName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSCityName() {
        return sCityName;
    }

    /**
     * Sets the value of the sCityName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSCityName(String value) {
        this.sCityName = value;
    }

    /**
     * Gets the value of the sWikipediaURL property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSWikipediaURL() {
        return sWikipediaURL;
    }

    /**
     * Sets the value of the sWikipediaURL property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSWikipediaURL(String value) {
        this.sWikipediaURL = value;
    }

    /**
     * Gets the value of the sGoogleMapsURL property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSGoogleMapsURL() {
        return sGoogleMapsURL;
    }

    /**
     * Sets the value of the sGoogleMapsURL property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSGoogleMapsURL(String value) {
        this.sGoogleMapsURL = value;
    }

}
