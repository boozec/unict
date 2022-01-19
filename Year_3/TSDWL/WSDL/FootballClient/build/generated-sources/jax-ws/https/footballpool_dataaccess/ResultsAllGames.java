
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
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
 *         &lt;element name="iGroupId" type="{http://www.w3.org/2001/XMLSchema}int"/>
 *         &lt;element name="iLevel" type="{http://www.w3.org/2001/XMLSchema}int"/>
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
    "iGroupId",
    "iLevel"
})
@XmlRootElement(name = "ResultsAllGames")
public class ResultsAllGames {

    protected int iGroupId;
    protected int iLevel;

    /**
     * Gets the value of the iGroupId property.
     * 
     */
    public int getIGroupId() {
        return iGroupId;
    }

    /**
     * Sets the value of the iGroupId property.
     * 
     */
    public void setIGroupId(int value) {
        this.iGroupId = value;
    }

    /**
     * Gets the value of the iLevel property.
     * 
     */
    public int getILevel() {
        return iLevel;
    }

    /**
     * Sets the value of the iLevel property.
     * 
     */
    public void setILevel(int value) {
        this.iLevel = value;
    }

}
