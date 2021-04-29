export function defaultCpuTemperatureTransformer(value) {

    return Math.trunc(Number(value)/1000);
}

export function defaultCpuFrequencyTransformer(value) {

    return Math.trunc(Number(value)/1000);
}

export function defaultIntPercentTransformer(value) {

    return Math.trunc(value * 100)
}

export function defaultReturnTransformer(value){
    return value;
}

export function defautlSpeedTransformer(value) {
    return value/1000000;
}
