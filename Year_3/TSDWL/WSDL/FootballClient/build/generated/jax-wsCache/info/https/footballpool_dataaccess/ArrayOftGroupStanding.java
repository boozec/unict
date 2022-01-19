
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftGroupStanding complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftGroupStanding">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tGroupStanding" type="{https://footballpool.dataaccess.eu}tGroupStanding" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftGroupStanding", propOrder = {
    "tGroupStanding"
})
public class ArrayOftGroupStanding {

    @XmlElement(nillable = true)
    protected List<TGroupStanding> tGroupStanding;

    /**
     * Gets the value of the tGroupStanding property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tGroupStanding property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTGroupStanding().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TGroupStanding }
     * 
     * 
     */
    public List<TGroupStanding> getTGroupStanding() {
        if (tGroupStanding == null) {
            tGroupStanding = new ArrayList<TGroupStanding>();
        }
        return this.tGroupStanding;
    }

}
