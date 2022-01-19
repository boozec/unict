
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for tTopScorerTop5 complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="tTopScorerTop5">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iRank" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iGoals" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="sName" type="{http://www.w3.org/2001/XMLSchema}string"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "tTopScorerTop5", propOrder = {
    "iRank",
    "iGoals",
    "sName"
})
public class TTopScorerTop5 {

    protected int iRank;
    protected int iGoals;
    @XmlElement(required = true)
    protected String sName;

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

}
