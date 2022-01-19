
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
 *         &lt;element name="GroupInfoResult" type="{https://footballpool.dataaccess.eu}ArrayOftGroupInfo"/>
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
    "groupInfoResult"
})
@XmlRootElement(name = "GroupInfoResponse")
public class GroupInfoResponse {

    @XmlElement(name = "GroupInfoResult", required = true)
    protected ArrayOftGroupInfo groupInfoResult;

    /**
     * Gets the value of the groupInfoResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftGroupInfo }
     *     
     */
    public ArrayOftGroupInfo getGroupInfoResult() {
        return groupInfoResult;
    }

    /**
     * Sets the value of the groupInfoResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftGroupInfo }
     *     
     */
    public void setGroupInfoResult(ArrayOftGroupInfo value) {
        this.groupInfoResult = value;
    }

}
