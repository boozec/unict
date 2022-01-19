
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tGameResult complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tGameResult">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iGameNumber" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sDescription" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="dtLocalPlayDateTime" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="dtUTCPlayDateTime" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeamName1" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="sTeamName2" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="iScoreTeam1" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iScoreTeam2" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iRedCards" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iYellowCards" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sGroupCode" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *         &lt;element name="bFinished" type="{http://www.w3.org/2001/XMLSchema}boolean"/>
 *         &lt;element name="iPenaltiesWonTeam1" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iPenaltiesWonTeam2" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tGameResult", propOrder = {
    "iGameNumber",
    "sDescription",
    "dtLocalPlayDateTime",
    "dtUTCPlayDateTime",
    "sTeamName1",
    "sTeamName2",
    "iScoreTeam1",
    "iScoreTeam2",
    "iRedCards",
    "iYellowCards",
    "sGroupCode",
    "bFinished",
    "iPenaltiesWonTeam1",
    "iPenaltiesWonTeam2"
})
public class TGameResult {

    protected int iGameNumber;
    @XmlElement(required = true)
    protected String sDescription;
    @XmlElement(required = true)
    protected String dtLocalPlayDateTime;
    @XmlElement(required = true)
    protected String dtUTCPlayDateTime;
    @XmlElement(required = true)
    protected String sTeamName1;
    @XmlElement(required = true)
    protected String sTeamName2;
    protected int iScoreTeam1;
    protected int iScoreTeam2;
    protected int iRedCards;
    protected int iYellowCards;
    @XmlElement(required = true)
    protected String sGroupCode;
    protected boolean bFinished;
    protected int iPenaltiesWonTeam1;
    protected int iPenaltiesWonTeam2;

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
     * Gets the value of the dtLocalPlayDateTime property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getDtLocalPlayDateTime() {
        return dtLocalPlayDateTime;
    }

    /**
     * Sets the value of the dtLocalPlayDateTime property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setDtLocalPlayDateTime(String value) {
        this.dtLocalPlayDateTime = value;
    }

    /**
     * Gets the value of the dtUTCPlayDateTime property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getDtUTCPlayDateTime() {
        return dtUTCPlayDateTime;
    }

    /**
     * Sets the value of the dtUTCPlayDateTime property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setDtUTCPlayDateTime(String value) {
        this.dtUTCPlayDateTime = value;
    }

    /**
     * Gets the value of the sTeamName1 property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeamName1() {
        return sTeamName1;
    }

    /**
     * Sets the value of the sTeamName1 property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeamName1(String value) {
        this.sTeamName1 = value;
    }

    /**
     * Gets the value of the sTeamName2 property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSTeamName2() {
        return sTeamName2;
    }

    /**
     * Sets the value of the sTeamName2 property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSTeamName2(String value) {
        this.sTeamName2 = value;
    }

    /**
     * Gets the value of the iScoreTeam1 property.
     * 
     */
    public int getIScoreTeam1() {
        return iScoreTeam1;
    }

    /**
     * Sets the value of the iScoreTeam1 property.
     * 
     */
    public void setIScoreTeam1(int value) {
        this.iScoreTeam1 = value;
    }

    /**
     * Gets the value of the iScoreTeam2 property.
     * 
     */
    public int getIScoreTeam2() {
        return iScoreTeam2;
    }

    /**
     * Sets the value of the iScoreTeam2 property.
     * 
     */
    public void setIScoreTeam2(int value) {
        this.iScoreTeam2 = value;
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
     * Gets the value of the sGroupCode property.
     * 
     * @return
     *     possible object is
     *     {@link String }
     *     
     */
    public String getSGroupCode() {
        return sGroupCode;
    }

    /**
     * Sets the value of the sGroupCode property.
     * 
     * @param value
     *     allowed object is
     *     {@link String }
     *     
     */
    public void setSGroupCode(String value) {
        this.sGroupCode = value;
    }

    /**
     * Gets the value of the bFinished property.
     * 
     */
    public boolean isBFinished() {
        return bFinished;
    }

    /**
     * Sets the value of the bFinished property.
     * 
     */
    public void setBFinished(boolean value) {
        this.bFinished = value;
    }

    /**
     * Gets the value of the iPenaltiesWonTeam1 property.
     * 
     */
    public int getIPenaltiesWonTeam1() {
        return iPenaltiesWonTeam1;
    }

    /**
     * Sets the value of the iPenaltiesWonTeam1 property.
     * 
     */
    public void setIPenaltiesWonTeam1(int value) {
        this.iPenaltiesWonTeam1 = value;
    }

    /**
     * Gets the value of the iPenaltiesWonTeam2 property.
     * 
     */
    public int getIPenaltiesWonTeam2() {
        return iPenaltiesWonTeam2;
    }

    /**
     * Sets the value of the iPenaltiesWonTeam2 property.
     * 
     */
    public void setIPenaltiesWonTeam2(int value) {
        this.iPenaltiesWonTeam2 = value;
    }

}
