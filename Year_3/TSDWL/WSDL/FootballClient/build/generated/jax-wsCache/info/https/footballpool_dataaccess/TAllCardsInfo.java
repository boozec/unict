
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlSchemaType;
import javax.xml.bind.annotation.XmlType;
import javax.xml.datatype.XMLGregorianCalendar;


/**
 * <p>Java class for tAllCardsInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tAllCardsInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="dDate" type="{http://www.w3.org/2001/XMLSchema}date"/>
 *         &lt;element name="iMinute" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sTeam1Name" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeam1Flag" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeam2Name" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeam2Flag" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sPlayerName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iYellow" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iRed" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tAllCardsInfo", propOrder = {
    "dDate",
    "iMinute",
    "sTeam1Name",
    "sTeam1Flag",
    "sTeam2Name",
    "sTeam2Flag",
    "sPlayerName",
    "iYellow",
    "iRed"
})
public class TAllCardsInfo {

    @XmlElement(required = true)
    @XmlSchemaType(name = "date")
    protected XMLGregorianCalendar dDate;
    protected int iMinute;
    @XmlElement(required = true)
    protected String sTeam1Name;
    @XmlElement(required = true)
    protected String sTeam1Flag;
    @XmlElement(required = true)
    protected String sTeam2Name;
    @XmlElement(required = true)
    protected String sTeam2Flag;
    @XmlElement(required = true)
    protected String sPlayerName;
    protected int iYellow;
    protected int iRed;

    /**
     * Gets the value of the dDate property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getDDate() {
        return dDate;
    }

    /**
     * Sets the value of the dDate property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setDDate(XMLGregorianCalendar value) {
        this.dDate = value;
    }

    /**
     * Gets the value of the iMinute property.
     * 
     */
    public int getIMinute() {
        return iMinute;
    }

    /**
     * Sets the value of the iMinute property.
     * 
     */
    public void setIMinute(int value) {
        this.iMinute = value;
    }

    /**
     * Gets the value of the sTeam1Name property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam1Name() {
        return sTeam1Name;
    }

    /**
     * Sets the value of the sTeam1Name property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam1Name(String value) {
        this.sTeam1Name = value;
    }

    /**
     * Gets the value of the sTeam1Flag property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam1Flag() {
        return sTeam1Flag;
    }

    /**
     * Sets the value of the sTeam1Flag property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam1Flag(String value) {
        this.sTeam1Flag = value;
    }

    /**
     * Gets the value of the sTeam2Name property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam2Name() {
        return sTeam2Name;
    }

    /**
     * Sets the value of the sTeam2Name property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam2Name(String value) {
        this.sTeam2Name = value;
    }

    /**
     * Gets the value of the sTeam2Flag property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam2Flag() {
        return sTeam2Flag;
    }

    /**
     * Sets the value of the sTeam2Flag property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam2Flag(String value) {
        this.sTeam2Flag = value;
    }

    /**
     * Gets the value of the sPlayerName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSPlayerName() {
        return sPlayerName;
    }

    /**
     * Sets the value of the sPlayerName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSPlayerName(String value) {
        this.sPlayerName = value;
    }

    /**
     * Gets the value of the iYellow property.
     * 
     */
    public int getIYellow() {
        return iYellow;
    }

    /**
     * Sets the value of the iYellow property.
     * 
     */
    public void setIYellow(int value) {
        this.iYellow = value;
    }

    /**
     * Gets the value of the iRed property.
     * 
     */
    public int getIRed() {
        return iRed;
    }

    /**
     * Sets the value of the iRed property.
     * 
     */
    public void setIRed(int value) {
        this.iRed = value;
    }

}
