
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for anonymous complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType>
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="iGameNumber" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iTeamId" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "", propOrder = {
    "iGameNumber",
    "iTeamId"
})
@XmlRootElement(name = "GameTeamScore")
public class GameTeamScore {

    protected int iGameNumber;
    protected int iTeamId;

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

}
