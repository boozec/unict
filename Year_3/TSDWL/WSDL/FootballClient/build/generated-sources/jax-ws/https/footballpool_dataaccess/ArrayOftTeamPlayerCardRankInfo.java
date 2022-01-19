
package https.footballpool_dataaccess;

import java.util.ArrayList;
import java.util.List;
import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlType;


/**
 * <p>Java class for ArrayOftTeamPlayerCardRankInfo complex type.
 * 
 * <p>The following schema fragment specifies the expected content contained within this class.
 * 
 * <pre>
 * &lt;complexType name="ArrayOftTeamPlayerCardRankInfo">
 *   &lt;complexContent>
 *     &lt;restriction base="{http://www.w3.org/2001/XMLSchema}anyType">
 *       &lt;sequence>
 *         &lt;element name="tTeamPlayerCardRankInfo" type="{https://footballpool.dataaccess.eu}tTeamPlayerCardRankInfo" maxOccurs="unbounded" minOccurs="0"/>
 *       &lt;/sequence>
 *     &lt;/restriction>
 *   &lt;/complexContent>
 * &lt;/complexType>
 * </pre>
 * 
 * 
 */
@XmlAccessorType(XmlAccessType.FIELD)
@XmlType(name = "ArrayOftTeamPlayerCardRankInfo", propOrder = {
    "tTeamPlayerCardRankInfo"
})
public class ArrayOftTeamPlayerCardRankInfo {

    @XmlElement(nillable = true)
    protected List<TTeamPlayerCardRankInfo> tTeamPlayerCardRankInfo;

    /**
     * Gets the value of the tTeamPlayerCardRankInfo property.
     * 
     * <p>
     * This accessor method returns a reference to the live list,
     * not a snapshot. Therefore any modification you make to the
     * returned list will be present inside the JAXB object.
     * This is why there is not a <CODE>set</CODE> method for the tTeamPlayerCardRankInfo property.
     * 
     * <p>
     * For example, to add a new item, do as follows:
     * <pre>
     *    getTTeamPlayerCardRankInfo().add(newItem);
     * </pre>
     * 
     * 
     * <p>
     * Objects of the following type(s) are allowed in the list
     * {@link TTeamPlayerCardRankInfo }
     * 
     * 
     */
    public List<TTeamPlayerCardRankInfo> getTTeamPlayerCardRankInfo() {
        if (tTeamPlayerCardRankInfo == null) {
            tTeamPlayerCardRankInfo = new ArrayList<TTeamPlayerCardRankInfo>();
        }
        return this.tTeamPlayerCardRankInfo;
    }

}
