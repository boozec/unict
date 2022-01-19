
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tGroupStanding complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tGroupStanding">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iTeamId" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sTeamName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iPlayed" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iWon" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iDraw" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iLost" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iGoalsFor" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iGoalsAgainst" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iPlusMin" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iPoints" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tGroupStanding", propOrder = {
    "iTeamId",
    "sTeamName",
    "iPlayed",
    "iWon",
    "iDraw",
    "iLost",
    "iGoalsFor",
    "iGoalsAgainst",
    "iPlusMin",
    "iPoints"
})
public class TGroupStanding {

    protected int iTeamId;
    @XmlElement(required = true)
    protected String sTeamName;
    protected int iPlayed;
    protected int iWon;
    protected int iDraw;
    protected int iLost;
    protected int iGoalsFor;
    protected int iGoalsAgainst;
    protected int iPlusMin;
    protected int iPoints;

    /**
     * Gets the value of the iTeamId property.
     * 
     */
    public int getITeamId() {
        return iTeamId;
    }

    /**
     * Sets the value of the iTeamId property.
     * 
     */
    public void setITeamId(int value) {
        this.iTeamId = value;
    }

    /**
     * Gets the value of the sTeamName property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeamName() {
        return sTeamName;
    }

    /**
     * Sets the value of the sTeamName property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeamName(String value) {
        this.sTeamName = value;
    }

    /**
     * Gets the value of the iPlayed property.
     * 
     */
    public int getIPlayed() {
        return iPlayed;
    }

    /**
     * Sets the value of the iPlayed property.
     * 
     */
    public void setIPlayed(int value) {
        this.iPlayed = value;
    }

    /**
     * Gets the value of the iWon property.
     * 
     */
    public int getIWon() {
        return iWon;
    }

    /**
     * Sets the value of the iWon property.
     * 
     */
    public void setIWon(int value) {
        this.iWon = value;
    }

    /**
     * Gets the value of the iDraw property.
     * 
     */
    public int getIDraw() {
        return iDraw;
    }

    /**
     * Sets the value of the iDraw property.
     * 
     */
    public void setIDraw(int value) {
        this.iDraw = value;
    }

    /**
     * Gets the value of the iLost property.
     * 
     */
    public int getILost() {
        return iLost;
    }

    /**
     * Sets the value of the iLost property.
     * 
     */
    public void setILost(int value) {
        this.iLost = value;
    }

    /**
     * Gets the value of the iGoalsFor property.
     * 
     */
    public int getIGoalsFor() {
        return iGoalsFor;
    }

    /**
     * Sets the value of the iGoalsFor property.
     * 
     */
    public void setIGoalsFor(int value) {
        this.iGoalsFor = value;
    }

    /**
     * Gets the value of the iGoalsAgainst property.
     * 
     */
    public int getIGoalsAgainst() {
        return iGoalsAgainst;
    }

    /**
     * Sets the value of the iGoalsAgainst property.
     * 
     */
    public void setIGoalsAgainst(int value) {
        this.iGoalsAgainst = value;
    }

    /**
     * Gets the value of the iPlusMin property.
     * 
     */
    public int getIPlusMin() {
        return iPlusMin;
    }

    /**
     * Sets the value of the iPlusMin property.
     * 
     */
    public void setIPlusMin(int value) {
        this.iPlusMin = value;
    }

    /**
     * Gets the value of the iPoints property.
     * 
     */
    public int getIPoints() {
        return iPoints;
    }

    /**
     * Sets the value of the iPoints property.
     * 
     */
    public void setIPoints(int value) {
        this.iPoints = value;
    }

}
