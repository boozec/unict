
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
 *         &lt;element name="AllPlayersWithRoleResult" type="{https://footballpool.dataaccess.eu}ArrayOftTeamPlayerName"/>
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
    "allPlayersWithRoleResult"
})
@XmlRootElement(name = "AllPlayersWithRoleResponse")
public class AllPlayersWithRoleResponse {

    @XmlElement(name = "AllPlayersWithRoleResult", required = true)
    protected ArrayOftTeamPlayerName allPlayersWithRoleResult;

    /**
     * Gets the value of the allPlayersWithRoleResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftTeamPlayerName }
     *     
     */
    public ArrayOftTeamPlayerName getAllPlayersWithRoleResult() {
        return allPlayersWithRoleResult;
    }

    /**
     * Sets the value of the allPlayersWithRoleResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftTeamPlayerName }
     *     
     */
    public void setAllPlayersWithRoleResult(ArrayOftTeamPlayerName value) {
        this.allPlayersWithRoleResult = value;
    }

}
