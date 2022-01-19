
package https.footballpool_dataaccess;

import javax.xml.bind.annotation.XmlAccessType;
import javax.xml.bind.annotation.XmlAccessorType;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlSchemaType;
import javax.xml.bind.annotation.XmlType;
import javax.xml.datatype.XMLGregorianCalendar;


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
 *         &lt;element name="LevelFirstGameDateResult" type="{http://www.w3.org/2001/XMLSchema}date"/>
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
    "levelFirstGameDateResult"
})
@XmlRootElement(name = "LevelFirstGameDateResponse")
public class LevelFirstGameDateResponse {

    @XmlElement(name = "LevelFirstGameDateResult", required = true)
    @XmlSchemaType(name = "date")
    protected XMLGregorianCalendar levelFirstGameDateResult;

    /**
     * Gets the value of the levelFirstGameDateResult property.
     * 
     * @return
     *     possible object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public XMLGregorianCalendar getLevelFirstGameDateResult() {
        return levelFirstGameDateResult;
    }

    /**
     * Sets the value of the levelFirstGameDateResult property.
     * 
     * @param value
     *     allowed object is
     *     {@link XMLGregorianCalendar }
     *     
     */
    public void setLevelFirstGameDateResult(XMLGregorianCalendar value) {
        this.levelFirstGameDateResult = value;
    }

}
