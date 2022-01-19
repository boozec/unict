
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
 *         &lt;element name="PlayerRolesResult" type="{https://footballpool.dataaccess.eu}ArrayOftPlayerRole"/>
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
    "playerRolesResult"
})
@XmlRootElement(name = "PlayerRolesResponse")
public class PlayerRolesResponse {

    @XmlElement(name = "PlayerRolesResult", required = true)
    protected ArrayOftPlayerRole playerRolesResult;

    /**
     * Gets the value of the playerRolesResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftPlayerRole }
     *     
     */
    public ArrayOftPlayerRole getPlayerRolesResult() {
        return playerRolesResult;
    }

    /**
     * Sets the value of the playerRolesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftPlayerRole }
     *     
     */
    public void setPlayerRolesResult(ArrayOftPlayerRole value) {
        this.playerRolesResult = value;
    }

}
