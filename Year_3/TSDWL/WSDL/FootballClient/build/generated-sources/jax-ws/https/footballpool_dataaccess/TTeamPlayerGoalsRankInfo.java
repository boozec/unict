
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tTeamPlayerGoalsRankInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tTeamPlayerGoalsRankInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iRank" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iID" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iGoals" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tTeamPlayerGoalsRankInfo", propOrder = {
    "iRank",
    "iid",
    "sName",
    "iGoals"
})
public class TTeamPlayerGoalsRankInfo {

    protected int iRank;
    @XmlElement(name = "iID")
    protected int iid;
    @XmlElement(required = true)
    protected String sName;
    protected int iGoals;

    /**
     * Gets the value of the iRank property.
     * 
     */
    public int getIRank() {
        return iRank;
    }

    /**
     * Sets the value of the iRank property.
     * 
     */
    public void setIRank(int value) {
        this.iRank = value;
    }

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
     * Gets the value of the iGoals property.
     * 
     */
    public int getIGoals() {
        return iGoals;
    }

    /**
     * Sets the value of the iGoals property.
     * 
     */
    public void setIGoals(int value) {
        this.iGoals = value;
    }

}
