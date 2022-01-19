
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
 *         &lt;element name="PlayersResult" type="{https://footballpool.dataaccess.eu}ArrayOftPlayer"/>
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
    "playersResult"
})
@XmlRootElement(name = "PlayersResponse")
public class PlayersResponse {

    @XmlElement(name = "PlayersResult", required = true)
    protected ArrayOftPlayer playersResult;

    /**
     * Gets the value of the playersResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftPlayer }
     *     
     */
    public ArrayOftPlayer getPlayersResult() {
        return playersResult;
    }

    /**
     * Sets the value of the playersResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftPlayer }
     *     
     */
    public void setPlayersResult(ArrayOftPlayer value) {
        this.playersResult = value;
    }

}
