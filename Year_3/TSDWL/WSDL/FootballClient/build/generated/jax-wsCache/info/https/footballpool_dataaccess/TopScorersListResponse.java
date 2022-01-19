
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
 *         &lt;element name="TopScorersListResult" type="{https://footballpool.dataaccess.eu}ArrayOftTopScorerTop5"/>
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
    "topScorersListResult"
})
@XmlRootElement(name = "TopScorersListResponse")
public class TopScorersListResponse {

    @XmlElement(name = "TopScorersListResult", required = true)
    protected ArrayOftTopScorerTop5 topScorersListResult;

    /**
     * Gets the value of the topScorersListResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftTopScorerTop5 }
     *     
     */
    public ArrayOftTopScorerTop5 getTopScorersListResult() {
        return topScorersListResult;
    }

    /**
     * Sets the value of the topScorersListResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftTopScorerTop5 }
     *     
     */
    public void setTopScorersListResult(ArrayOftTopScorerTop5 value) {
        this.topScorersListResult = value;
    }

}
