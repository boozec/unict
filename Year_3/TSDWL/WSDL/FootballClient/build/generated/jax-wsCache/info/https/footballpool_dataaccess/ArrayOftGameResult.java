
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftGameResult complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftGameResult">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tGameResult" type="{https://footballpool.dataaccess.eu}tGameResult" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftGameResult", propOrder = {
    "tGameResult"
})
public class ArrayOftGameResult {

    @XmlElement(nillable = true)
    protected List<TGameResult> tGameResult;

    /**
     * Gets the value of the tGameResult property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tGameResult property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTGameResult().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TGameResult }
     * 
     * 
     */
    public List<TGameResult> getTGameResult() {
        if (tGameResult == null) {
            tGameResult = new ArrayList<TGameResult>();
        }
        return this.tGameResult;
    }

}
