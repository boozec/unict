
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tPlayer complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tPlayer">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iId" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sFullName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sFirstName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sLastName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tPlayer", propOrder = {
    "iId",
    "sName",
    "sFullName",
    "sFirstName",
    "sLastName"
})
public class TPlayer {

    protected int iId;
    @XmlElement(required = true)
    protected String sName;
    @XmlElement(required = true)
    protected String sFullName;
    @XmlElement(required = true)
    protected String sFirstName;
    @XmlElement(required = true)
    protected String sLastName;

    /**
     * Gets the value of the iId property.
     * 
     */
    public int getIId() {
        return iId;
    }

    /**
     * Sets the value of the iId property.
     * 
     */
    public void setIId(int value) {
        this.iId = value;
    }

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
     * Gets the value of the sFullName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSFullName() {
        return sFullName;
    }

    /**
     * Sets the value of the sFullName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSFullName(String value) {
        this.sFullName = value;
    }

    /**
     * Gets the value of the sFirstName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSFirstName() {
        return sFirstName;
    }

    /**
     * Sets the value of the sFirstName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSFirstName(String value) {
        this.sFirstName = value;
    }

    /**
     * Gets the value of the sLastName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSLastName() {
        return sLastName;
    }

    /**
     * Sets the value of the sLastName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSLastName(String value) {
        this.sLastName = value;
    }

}
