import FarmBean from '../common/bean/FarmBean';
//目前是随机变动
export class MainViewModel {
    getFarmData(fieldId) {
        let farmBean = new FarmBean(1, '老张的玉米地', 22.5, 56, 30, 800, 25);
        farmBean.temperature = farmBean.temperature + Math.floor(Math.random() * 5); //温度
        farmBean.humidity = farmBean.humidity + Math.floor(Math.random() * 5); //空气湿度
        farmBean.lumination = farmBean.lumination + Math.floor(Math.random() * 5); //光照
        farmBean.co2 = farmBean.co2 + Math.floor(Math.random() * 5); //二氧化碳浓度
        farmBean.soilHumidity = farmBean.soilHumidity + Math.floor(Math.random() * 5); //土壤湿度
        return farmBean;
    }
}
export default new MainViewModel();
//# sourceMappingURL=MainViewModel.js.map