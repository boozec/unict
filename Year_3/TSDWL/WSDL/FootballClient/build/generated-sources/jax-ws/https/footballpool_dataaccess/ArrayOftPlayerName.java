
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftPlayerName complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftPlayerName">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tPlayerName" type="{https://footballpool.dataaccess.eu}tPlayerName" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftPlayerName", propOrder = {
    "tPlayerName"
})
public class ArrayOftPlayerName {

    @XmlElement(nillable = true)
    protected List<TPlayerName> tPlayerName;

    /**
     * Gets the value of the tPlayerName property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tPlayerName property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTPlayerName().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TPlayerName }
     * 
     * 
     */
    public List<TPlayerName> getTPlayerName() {
        if (tPlayerName == null) {
            tPlayerName = new ArrayList<TPlayerName>();
        }
        return this.tPlayerName;
    }

}
