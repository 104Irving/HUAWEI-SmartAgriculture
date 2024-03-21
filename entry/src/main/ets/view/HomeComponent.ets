import FarmBean from '../common/bean/FarmBean';
import MainViewModel from '../model/MainViewModel';

@Component
export default struct HomeComponent {
  @State farmBean: FarmBean = new FarmBean(1, '老张的玉米地', 22.5, 56, 30, 800, 25);
  @State Ifdetailshow: boolean = false;
  private timerId: number = 0; //计时器id，每5秒读取一次数据

  @Builder ElementShow(name: String, detail: number) {
    Row() {
      Text(`${name}`)
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
      Text(`${detail}`)
        .fontSize(20)
    }
    .width('95%')
    .justifyContent(FlexAlign.SpaceBetween)
  }

  @Builder DetialShow() {
    if (this.Ifdetailshow) {
      Divider()
        .width('95%')
      Text('传感器数据')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider()
        .width('95%')
      this.ElementShow('温度', this.farmBean.temperature)
      this.ElementShow('空气湿度', this.farmBean.humidity)
      this.ElementShow('二氧化碳', this.farmBean.co2)
      this.ElementShow('光照', this.farmBean.lumination)
      this.ElementShow('二氧化碳', this.farmBean.co2)
      this.ElementShow('土壤湿度', this.farmBean.soilHumidity)
    }
  }

  build() {
    Column({ space: 8 }) {
      Text('选择农田')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider().width('95%')
      Row() {
        // SelectEvent({
        //   Ifdetailshow: $Ifdetailshow
        // })
        Select([
          { value: '一号田', icon: $r('app.media.leaf') },
          { value: '二号田', icon: $r('app.media.leaf') },
          { value: '三号田', icon: $r('app.media.leaf') },
          { value: '四号田', icon: $r('app.media.leaf') },
          { value: '五号田', icon: $r('app.media.leaf') }])
          .selected(0)
          .value('选择农田')
          .font({ size: 24, weight: 600 })
          .fontColor('#182431')
          .selectedOptionFont({ size: 22, weight: 600 })
          .optionFont({ size: 18, weight: 500 })
          .onSelect((index: number)=>{
            this.Ifdetailshow = true;
          })
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Text(this.Ifdetailshow?'true':'false')

      this.DetialShow()
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}

@Component
export struct SelectEvent{
  @Link @Watch('onClickIndexChanged') Ifdetailshow: Boolean;
  onClickIndexChanged(){
    this.Ifdetailshow = true;
  }

  build(){
    Select([
      { value: '一号田', icon: $r('app.media.leaf') },
      { value: '二号田', icon: $r('app.media.leaf') },
      { value: '三号田', icon: $r('app.media.leaf') },
      { value: '四号田', icon: $r('app.media.leaf') },
      { value: '五号田', icon: $r('app.media.leaf') }])
      .selected(0)
      .value('选择农田')
      .font({ size: 24, weight: 600 })
      .fontColor('#182431')
      .selectedOptionFont({ size: 22, weight: 600 })
      .optionFont({ size: 18, weight: 500 })
      .onClick(() => {
        this.Ifdetailshow = true;
        console.info("it is true");
      })
  }
}