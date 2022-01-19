
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
 *         &lt;element name="GroupStandingsResult" type="{https://footballpool.dataaccess.eu}ArrayOftGroupStanding"/>
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
    "groupStandingsResult"
})
@XmlRootElement(name = "GroupStandingsResponse")
public class GroupStandingsResponse {

    @XmlElement(name = "GroupStandingsResult", required = true)
    protected ArrayOftGroupStanding groupStandingsResult;

    /**
     * Gets the value of the groupStandingsResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftGroupStanding }
     *     
     */
    public ArrayOftGroupStanding getGroupStandingsResult() {
        return groupStandingsResult;
    }

    /**
     * Sets the value of the groupStandingsResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftGroupStanding }
     *     
     */
    public void setGroupStandingsResult(ArrayOftGroupStanding value) {
        this.groupStandingsResult = value;
    }

}
