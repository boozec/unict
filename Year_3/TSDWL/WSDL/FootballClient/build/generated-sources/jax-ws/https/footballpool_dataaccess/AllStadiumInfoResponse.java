
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
 *         &lt;element name="AllStadiumInfoResult" type="{https://footballpool.dataaccess.eu}ArrayOftStadiumInfo"/>
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
    "allStadiumInfoResult"
})
@XmlRootElement(name = "AllStadiumInfoResponse")
public class AllStadiumInfoResponse {

    @XmlElement(name = "AllStadiumInfoResult", required = true)
    protected ArrayOftStadiumInfo allStadiumInfoResult;

    /**
     * Gets the value of the allStadiumInfoResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftStadiumInfo }
     *     
     */
    public ArrayOftStadiumInfo getAllStadiumInfoResult() {
        return allStadiumInfoResult;
    }

    /**
     * Sets the value of the allStadiumInfoResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftStadiumInfo }
     *     
     */
    public void setAllStadiumInfoResult(ArrayOftStadiumInfo value) {
        this.allStadiumInfoResult = value;
    }

}
