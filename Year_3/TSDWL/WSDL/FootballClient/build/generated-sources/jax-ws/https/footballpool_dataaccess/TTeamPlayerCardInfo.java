
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tTeamPlayerCardInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tTeamPlayerCardInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iID" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iYellowCards" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iRedCards" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tTeamPlayerCardInfo", propOrder = {
    "iid",
    "sName",
    "iYellowCards",
    "iRedCards"
})
public class TTeamPlayerCardInfo {

    @XmlElement(name = "iID")
    protected int iid;
    @XmlElement(required = true)
    protected String sName;
    protected int iYellowCards;
    protected int iRedCards;

    /**
     * Gets the value of the iid property.
     * 
     */
    public int getIID() {
        return iid;
    }

    /**
     * Sets the value of the iid property.
     * 
     */
    public void setIID(int value) {
        this.iid = value;
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
     * Gets the value of the iYellowCards property.
     * 
     */
    public int getIYellowCards() {
        return iYellowCards;
    }

    /**
     * Sets the value of the iYellowCards property.
     * 
     */
    public void setIYellowCards(int value) {
        this.iYellowCards = value;
    }

    /**
     * Gets the value of the iRedCards property.
     * 
     */
    public int getIRedCards() {
        return iRedCards;
    }

    /**
     * Sets the value of the iRedCards property.
     * 
     */
    public void setIRedCards(int value) {
        this.iRedCards = value;
    }

}
