
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftTopScorerTop5 complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftTopScorerTop5">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tTopScorerTop5" type="{https://footballpool.dataaccess.eu}tTopScorerTop5" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftTopScorerTop5", propOrder = {
    "tTopScorerTop5"
})
public class ArrayOftTopScorerTop5 {

    @XmlElement(nillable = true)
    protected List<TTopScorerTop5> tTopScorerTop5;

    /**
     * Gets the value of the tTopScorerTop5 property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tTopScorerTop5 property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTTopScorerTop5().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TTopScorerTop5 }
     * 
     * 
     */
    public List<TTopScorerTop5> getTTopScorerTop5() {
        if (tTopScorerTop5 == null) {
            tTopScorerTop5 = new ArrayList<TTopScorerTop5>();
        }
        return this.tTopScorerTop5;
    }

}
