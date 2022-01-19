
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
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
 *         &lt;element name="GameIDsGroupedByCityResult" type="{https://footballpool.dataaccess.eu}ArrayOftGameIDsPerCity"/>
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
    "gameIDsGroupedByCityResult"
})
@XmlRootElement(name = "GameIDsGroupedByCityResponse")
public class GameIDsGroupedByCityResponse {

    @XmlElement(name = "GameIDsGroupedByCityResult", required = true)
    protected ArrayOftGameIDsPerCity gameIDsGroupedByCityResult;

    /**
     * Gets the value of the gameIDsGroupedByCityResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftGameIDsPerCity }
     *     
     */
    public ArrayOftGameIDsPerCity getGameIDsGroupedByCityResult() {
        return gameIDsGroupedByCityResult;
    }

    /**
     * Sets the value of the gameIDsGroupedByCityResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftGameIDsPerCity }
     *     
     */
    public void setGameIDsGroupedByCityResult(ArrayOftGameIDsPerCity value) {
        this.gameIDsGroupedByCityResult = value;
    }

}
