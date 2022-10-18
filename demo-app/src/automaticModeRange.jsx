import React from "react";
import { useState } from "react";
import RangeSlider from "react-bootstrap-range-slider"
import { DEFAULT_MAX_TIMER, DEFAULT_MIN_TIMER } from "./homepage";
const AutomaticModeRange = (props) => {

    const [value, setValue] = useState(props.timerValue)

    return (
        <>
            <RangeSlider tooltip="off" min={DEFAULT_MIN_TIMER} max={DEFAULT_MAX_TIMER} step={1}
                value={value} style={{ fontSize: "27px" }}
                tooltipLabel={value => `${value} sec`}
                onChange={changeEvent => setValue(changeEvent.target.value)}
                onAfterChange={() => props.setTimerValue(value)}
                disabled={props.disabled}
            />
        </>
    )
}

export default AutomaticModeRange