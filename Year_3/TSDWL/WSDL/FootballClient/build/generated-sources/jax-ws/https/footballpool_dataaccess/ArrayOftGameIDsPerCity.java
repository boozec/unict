
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftGameIDsPerCity complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftGameIDsPerCity">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tGameIDsPerCity" type="{https://footballpool.dataaccess.eu}tGameIDsPerCity" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftGameIDsPerCity", propOrder = {
    "tGameIDsPerCity"
})
public class ArrayOftGameIDsPerCity {

    @XmlElement(nillable = true)
    protected List<TGameIDsPerCity> tGameIDsPerCity;

    /**
     * Gets the value of the tGameIDsPerCity property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tGameIDsPerCity property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTGameIDsPerCity().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TGameIDsPerCity }
     * 
     * 
     */
    public List<TGameIDsPerCity> getTGameIDsPerCity() {
        if (tGameIDsPerCity == null) {
            tGameIDsPerCity = new ArrayList<TGameIDsPerCity>();
        }
        return this.tGameIDsPerCity;
    }

}
