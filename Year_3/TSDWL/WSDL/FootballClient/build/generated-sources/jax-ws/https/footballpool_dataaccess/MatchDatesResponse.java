
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
 *         &lt;element name="MatchDatesResult" type="{https://footballpool.dataaccess.eu}ArrayOfdate"/>
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
    "matchDatesResult"
})
@XmlRootElement(name = "MatchDatesResponse")
public class MatchDatesResponse {

    @XmlElement(name = "MatchDatesResult", required = true)
    protected ArrayOfdate matchDatesResult;

    /**
     * Gets the value of the matchDatesResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOfdate }
     *     
     */
    public ArrayOfdate getMatchDatesResult() {
        return matchDatesResult;
    }

    /**
     * Sets the value of the matchDatesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOfdate }
     *     
     */
    public void setMatchDatesResult(ArrayOfdate value) {
        this.matchDatesResult = value;
    }

}
