import React from "react";

const displayName = name => {
    switch (name) {
        case "Gyroscope":
            return "Gyroscope Sensor";

            
        case "Potentiometer":
            return "Voltage Sensor";
            
        case "Switch":
            return "Switch Status";             

        default:
            alert("Invalid Sensor Name: " + name)
            break;
    }
}

const sensorClicked = name =>{
    alert("Clicked: " + name)
    
}

const SensorUnit = (props) => {

    return (
        <button disabled={props.enabled} onClick={() => sensorClicked(props.name)} className="border border-2 border-dark rounded-pill pb-3 mt-2 mb-2" style={{justifyContent:'center'}}>
            <div className="row">
                <p>{displayName(props.name)}</p>                
            </div>
            <div className="row d-inline-flex bg-white ps-3 pe-3" style={{justifyContent:'center'}}>
                {
                    props.value != null ? 
                        <div>{props.value}</div> : 
                        <div>N/A</div>
                }
            </div>
        </button>
)}

export default SensorUnit