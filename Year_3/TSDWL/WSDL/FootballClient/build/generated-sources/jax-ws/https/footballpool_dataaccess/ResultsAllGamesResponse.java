
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
 *         &lt;element name="ResultsAllGamesResult" type="{https://footballpool.dataaccess.eu}ArrayOftGameResult"/>
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
    "resultsAllGamesResult"
})
@XmlRootElement(name = "ResultsAllGamesResponse")
public class ResultsAllGamesResponse {

    @XmlElement(name = "ResultsAllGamesResult", required = true)
    protected ArrayOftGameResult resultsAllGamesResult;

    /**
     * Gets the value of the resultsAllGamesResult property.
     * 
     * @return
     *     possible object is
     *     {@link ArrayOftGameResult }
     *     
     */
    public ArrayOftGameResult getResultsAllGamesResult() {
        return resultsAllGamesResult;
    }

    /**
     * Sets the value of the resultsAllGamesResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link ArrayOftGameResult }
     *     
     */
    public void setResultsAllGamesResult(ArrayOftGameResult value) {
        this.resultsAllGamesResult = value;
    }

}
