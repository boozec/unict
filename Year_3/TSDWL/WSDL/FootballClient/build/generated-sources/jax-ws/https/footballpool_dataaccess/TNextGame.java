
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tNextGame complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tNextGame">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iGameNumber" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sLocalDateTime" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sUTCDateTime" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeam1" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeam2" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tNextGame", propOrder = {
    "iGameNumber",
    "sLocalDateTime",
    "sutcDateTime",
    "sTeam1",
    "sTeam2"
})
public class TNextGame {

    protected int iGameNumber;
    @XmlElement(required = true)
    protected String sLocalDateTime;
    @XmlElement(name = "sUTCDateTime", required = true)
    protected String sutcDateTime;
    @XmlElement(required = true)
    protected String sTeam1;
    @XmlElement(required = true)
    protected String sTeam2;

    /**
     * Gets the value of the iGameNumber property.
     * 
     */
    public int getIGameNumber() {
        return iGameNumber;
    }

    /**
     * Sets the value of the iGameNumber property.
     * 
     */
    public void setIGameNumber(int value) {
        this.iGameNumber = value;
    }

    /**
     * Gets the value of the sLocalDateTime property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSLocalDateTime() {
        return sLocalDateTime;
    }

    /**
     * Sets the value of the sLocalDateTime property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSLocalDateTime(String value) {
        this.sLocalDateTime = value;
    }

    /**
     * Gets the value of the sutcDateTime property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSUTCDateTime() {
        return sutcDateTime;
    }

    /**
     * Sets the value of the sutcDateTime property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSUTCDateTime(String value) {
        this.sutcDateTime = value;
    }

    /**
     * Gets the value of the sTeam1 property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam1() {
        return sTeam1;
    }

    /**
     * Sets the value of the sTeam1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam1(String value) {
        this.sTeam1 = value;
    }

    /**
     * Gets the value of the sTeam2 property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeam2() {
        return sTeam2;
    }

    /**
     * Sets the value of the sTeam2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeam2(String value) {
        this.sTeam2 = value;
    }

}
