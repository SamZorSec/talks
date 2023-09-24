Java.perform(function() {
    const SIMULATED_LATITUDE  = <latitude>;
    const SIMULATED_LONGITUDE = <longitude>;
    
    // https://developer.android.com/reference/android/location/Location
    var Location = Java.use("android.location.Location");

    Location.getLatitude.overload().implementation = function() {
        console.log("\nLocation.getLatitude()");
        console.log("> Old: " + this.getLatitude());
        console.log("> New: " + SIMULATED_LATITUDE);

        return SIMULATED_LATITUDE;
    }

    Location.getLongitude.overload().implementation = function() {
        console.log("\nLocation.getLongitude()");
        console.log("> Old: " + this.getLongitude());
        console.log("> New: " + SIMULATED_LONGITUDE);

        return SIMULATED_LONGITUDE;
    }
});