
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftNextGame complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftNextGame">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tNextGame" type="{https://footballpool.dataaccess.eu}tNextGame" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftNextGame", propOrder = {
    "tNextGame"
})
public class ArrayOftNextGame {

    @XmlElement(nillable = true)
    protected List<TNextGame> tNextGame;

    /**
     * Gets the value of the tNextGame property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tNextGame property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTNextGame().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TNextGame }
     * 
     * 
     */
    public List<TNextGame> getTNextGame() {
        if (tNextGame == null) {
            tNextGame = new ArrayList<TNextGame>();
        }
        return this.tNextGame;
    }

}
