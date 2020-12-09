#!/usr/bin/env bash

# team-test-mz
#host=10.0.162.5
#port=32565
#jiashan-mingzhu
host="localhost"
port=1883
# hk-pre
#host=47.244.55.194
#port=31912

# map_id=47753

# current=`date "+%Y-%m-%d %H:%M:%S"`
# timeStamp=`date -d "$current" +%s`
# echo $timeStamp
# echo $current
# cTS=$((timeStamp*1000+`date "+%N"`/1000000))
# echo $cTS
#echo $rsu1_msg
# r1='{"timestamp":'$cTS',"vin":"rsu.hksp1","run_scene":"real.rsu","data":[{"K":"map","V":'$map_id'},{"K":"rsu_detection","V":[{"is_detection_valid":false,"mov_obj_list":{"objs":[],"ts":1588661825.870014},"ts":1588661825.870014,"rsu_info":{"x":302435.337385,"y":2471255.98771,"base64":"AAAAAAAAAAAVdHtZjXUSQQJIbf6r2kJBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAA"}}]}]}'
# r2='{"timestamp":'$cTS',"vin":"rsu.hksp2","run_scene":"real.rsu","data":[{"K":"map","V":'$map_id'},{"K":"rsu_detection","V":[{"is_detection_valid":false,"mov_obj_list":{"objs":[],"ts":1588661825.870014},"ts":1588661825.870014,"rsu_info":{"x":302435.337385,"y":2471255.98771,"base64":"AAAAAAAAAAAVdHtZjXUSQQJIbf6r2kJBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAA"}}]}]}'
# r3='{"timestamp":'$cTS',"vin":"rsu.hksp3","run_scene":"real.rsu","data":[{"K":"map","V":'$map_id'},{"K":"rsu_detection","V":[{"is_detection_valid":false,"mov_obj_list":{"objs":[],"ts":1588661825.870014},"ts":1588661825.870014,"rsu_info":{"x":302435.337385,"y":2471255.98771,"base64":"AAAAAAAAAAAVdHtZjXUSQQJIbf6r2kJBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAA"}}]}]}'
# r4='{"timestamp":'$cTS',"vin":"rsu.hksp4","run_scene":"real.rsu","data":[{"K":"map","V":'$map_id'},{"K":"rsu_detection","V":[{"is_detection_valid":false,"mov_obj_list":{"objs":[],"ts":1588661825.870014},"ts":1588661825.870014,"rsu_info":{"x":302435.337385,"y":2471255.98771,"base64":"AAAAAAAAAAAVdHtZjXUSQQJIbf6r2kJBAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAQAAAAAAAAAAAAAAAAAAAAAAAAA"}}]}]}'
light_status={\"params\":{\"lights\":[{\"id\":0,\"dir\":1,\"state\":1}]}}

while true; do
    mosquitto_pub -h $host -p $port  -t "/mqtt_backend/light_test/traffic_light_status" -m $light_status
    # mosquitto_pub -h $host -p $port -u compass -P compass -t "/efence_k8s_backend/logging/report" -m $r2
    # mosquitto_pub -h $host -p $port -u compass -P compass -t "/efence_k8s_backend/logging/report" -m $r3
    # mosquitto_pub -h $host -p $port -u compass -P compass -t "/efence_k8s_backend/logging/report" -m $r4
    sleep 5
done

# Send rsu_statistics to c-c MQTT
#while true; do
#    mosquitto_pub -h $host -p 32564 -u compass -P compass -t "compass/rsu_statistics/47753" -m '{[{"layby_zone_id": 0, "params": [{"diff_cars": [], "high_priority_car_number": 0, "dir": 0.25, "car_number": 0}, {"diff_cars": [], "high_priority_car_number": 0, "dir": 3.4, "car_number": 0}], "is_valid": true, "rsu_valid_info": [["rsu0", true], ["rsu1", true], ["rsu2", true], ["rsu3", true]], "all_rsu_is_valid": true}]}'
#    sleep 0.5
#done

