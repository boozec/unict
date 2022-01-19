
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlSchemaType;
import javax.xml.bind.annotation.XmlType;
import javax.xml.datatype.XMLGregorianCalendar;


/**
 * <p>Java class for tGroupInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tGroupInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iId" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iLevel" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sCode" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sDescription" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="dFirstGameDate" type="{http://www.w3.org/2001/XMLSchema}date"/>
 *         &lt;element name="dLastGameDate" type="{http://www.w3.org/2001/XMLSchema}date"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tGroupInfo", propOrder = {
    "iId",
    "iLevel",
    "sCode",
    "sDescription",
    "dFirstGameDate",
    "dLastGameDate"
})
public class TGroupInfo {

    protected int iId;
    protected int iLevel;
    @XmlElement(required = true)
    protected String sCode;
    @XmlElement(required = true)
    protected String sDescription;
    @XmlElement(required = true)
    @XmlSchemaType(name = "date")
    protected XMLGregorianCalendar dFirstGameDate;
    @XmlElement(required = true)
    @XmlSchemaType(name = "date")
    protected XMLGregorianCalendar dLastGameDate;

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
     * Gets the value of the iLevel property.
     * 
     */
    public int getILevel() {
        return iLevel;
    }

    /**
     * Sets the value of the iLevel property.
     * 
     */
    public void setILevel(int value) {
        this.iLevel = value;
    }

    /**
     * Gets the value of the sCode property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSCode() {
        return sCode;
    }

    /**
     * Sets the value of the sCode property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSCode(String value) {
        this.sCode = value;
    }

    /**
     * Gets the value of the sDescription property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSDescription() {
        return sDescription;
    }

    /**
     * Sets the value of the sDescription property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSDescription(String value) {
        this.sDescription = value;
    }

    /**
     * Gets the value of the dFirstGameDate property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getDFirstGameDate() {
        return dFirstGameDate;
    }

    /**
     * Sets the value of the dFirstGameDate property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setDFirstGameDate(XMLGregorianCalendar value) {
        this.dFirstGameDate = value;
    }

    /**
     * Gets the value of the dLastGameDate property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getDLastGameDate() {
        return dLastGameDate;
    }

    /**
     * Sets the value of the dLastGameDate property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setDLastGameDate(XMLGregorianCalendar value) {
        this.dLastGameDate = value;
    }

}
