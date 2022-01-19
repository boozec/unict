
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
 *         &lt;element name="CountriesResult" type="{https://footballpool.dataaccess.eu}ArrayOftCountry"/>
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
    "countriesResult"
})
@XmlRootElement(name = "CountriesResponse")
public class CountriesResponse {

    @XmlElement(name = "CountriesResult", required = true)
    protected ArrayOftCountry countriesResult;

    /**
     * Gets the value of the countriesResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftCountry }
     *     
     */
    public ArrayOftCountry getCountriesResult() {
        return countriesResult;
    }

    /**
     * Sets the value of the countriesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftCountry }
     *     
     */
    public void setCountriesResult(ArrayOftCountry value) {
        this.countriesResult = value;
    }

}
