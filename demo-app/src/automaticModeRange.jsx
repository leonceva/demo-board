import React from "react";
import { useState } from "react";
import RangeSlider from "react-bootstrap-range-slider"
const AutomaticModeRange = (props) => {

    const [value, setValue] = useState(props.timerValue)

    return(
        <>
            <RangeSlider tooltip="off" min={15} max={30} step={1} 
            value={value} style={{fontSize:"27px"}}
            tooltipLabel={value => `${value} sec`}
            onChange={changeEvent => setValue(changeEvent.target.value)}
            onAfterChange={() => props.setTimerValue(value)}
            disabled={props.disabled}
            />
        </>
    )
}

export default AutomaticModeRange