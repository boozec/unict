
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
 *         &lt;element name="FirstLastGamesEachLevelResult" type="{https://footballpool.dataaccess.eu}ArrayOftGameLevelInfo"/>
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
    "firstLastGamesEachLevelResult"
})
@XmlRootElement(name = "FirstLastGamesEachLevelResponse")
public class FirstLastGamesEachLevelResponse {

    @XmlElement(name = "FirstLastGamesEachLevelResult", required = true)
    protected ArrayOftGameLevelInfo firstLastGamesEachLevelResult;

    /**
     * Gets the value of the firstLastGamesEachLevelResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftGameLevelInfo }
     *     
     */
    public ArrayOftGameLevelInfo getFirstLastGamesEachLevelResult() {
        return firstLastGamesEachLevelResult;
    }

    /**
     * Sets the value of the firstLastGamesEachLevelResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftGameLevelInfo }
     *     
     */
    public void setFirstLastGamesEachLevelResult(ArrayOftGameLevelInfo value) {
        this.firstLastGamesEachLevelResult = value;
    }

}
