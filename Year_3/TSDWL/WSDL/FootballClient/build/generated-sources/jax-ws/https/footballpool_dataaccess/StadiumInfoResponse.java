
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
 *         &lt;element name="StadiumInfoResult" type="{https://footballpool.dataaccess.eu}tStadiumInfo"/>
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
    "stadiumInfoResult"
})
@XmlRootElement(name = "StadiumInfoResponse")
public class StadiumInfoResponse {

    @XmlElement(name = "StadiumInfoResult", required = true)
    protected TStadiumInfo stadiumInfoResult;

    /**
     * Gets the value of the stadiumInfoResult property.
     * 
     * @return
     *     possible object is
     *     {@link TStadiumInfo }
     *     
     */
    public TStadiumInfo getStadiumInfoResult() {
        return stadiumInfoResult;
    }

    /**
     * Sets the value of the stadiumInfoResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link TStadiumInfo }
     *     
     */
    public void setStadiumInfoResult(TStadiumInfo value) {
        this.stadiumInfoResult = value;
    }

}
