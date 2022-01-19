
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
 *         &lt;element name="TeamIDsByGroupResult" type="{https://footballpool.dataaccess.eu}ArrayOfInt"/>
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
    "teamIDsByGroupResult"
})
@XmlRootElement(name = "TeamIDsByGroupResponse")
public class TeamIDsByGroupResponse {

    @XmlElement(name = "TeamIDsByGroupResult", required = true)
    protected ArrayOfInt teamIDsByGroupResult;

    /**
     * Gets the value of the teamIDsByGroupResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOfInt }
     *     
     */
    public ArrayOfInt getTeamIDsByGroupResult() {
        return teamIDsByGroupResult;
    }

    /**
     * Sets the value of the teamIDsByGroupResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOfInt }
     *     
     */
    public void setTeamIDsByGroupResult(ArrayOfInt value) {
        this.teamIDsByGroupResult = value;
    }

}
