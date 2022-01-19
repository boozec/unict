
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
 *         &lt;element name="NextGamesResult" type="{https://footballpool.dataaccess.eu}ArrayOftNextGame"/>
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
    "nextGamesResult"
})
@XmlRootElement(name = "NextGamesResponse")
public class NextGamesResponse {

    @XmlElement(name = "NextGamesResult", required = true)
    protected ArrayOftNextGame nextGamesResult;

    /**
     * Gets the value of the nextGamesResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftNextGame }
     *     
     */
    public ArrayOftNextGame getNextGamesResult() {
        return nextGamesResult;
    }

    /**
     * Sets the value of the nextGamesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftNextGame }
     *     
     */
    public void setNextGamesResult(ArrayOftNextGame value) {
        this.nextGamesResult = value;
    }

}
