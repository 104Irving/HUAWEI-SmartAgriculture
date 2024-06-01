import axios from '@ohos/axios'

//对农田进行操作后上传数据到服务器的函数
function UploadData(params:any, Interface:any){//上传的参数,和接口
    axios({//传递到服务器请求用户管理农田的相关数据
      method:"get",
      url:`47.108.250.206:8080/${Interface}`,
      params: params
    }).then(res=>{
      if(res.data){
      }else{//数据获取失败
        // 数据获取失败的处理 todo
      }
    })
}

//数字文本输入弹窗
@CustomDialog
struct OperationTextSetDialog {
  @Link textValue: number
  @Link inputValue: number
  controller?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller
  // 以实现在CustomDialog中打开另一个或另一些CustomDialog
  // 那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {}
  confirm: () => void = () => {}

  build() {
    Column() {
      Text('设定阈值').fontSize(20).margin({ bottom: 10 })
      TextInput({ placeholder: '', text: String(this.textValue) }).height(60).width('90%')
        .onChange((value: string) => {
          this.inputValue = Number(value)
        })
      // Text('温度范围在10-40').fontSize(16).margin({ bottom: 10 })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            this.controller.close()
            this.cancel()

          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确定')
          .onClick(() => {
            if (this.controller != undefined) {
              this.textValue = this.inputValue
              this.controller.close()
              this.confirm()
            }
          }).backgroundColor(0xffffff).fontColor(Color.Red)
      }.margin({ bottom: 10 })
    }.borderRadius(10)
  }
}

//弹窗样例
// @CustomDialog
// struct CustomDialogExampleTwo {
//   controllerTwo?: CustomDialogController
//
//   build() {
//     Column() {
//       Text('我是第二个弹窗')
//         .fontSize(30)
//         .height(100)
//       Button('点我关闭第二个弹窗')
//         .onClick(() => {
//           if (this.controllerTwo != undefined) {
//             this.controllerTwo.close()
//           }
//         })
//         .margin(20)
//     }
//   }
// }

//灌溉界面
@Component
export struct WaterPlanComponent {
  @State selectTime: Date = new Date('2020-12-25T08:30:00')

  build() {
    Column({space:8}) {
      Text('手动灌溉')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')
      Row(){
        Text('开启水阀:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})
          .onChange((isOn:boolean)=>{
            if (isOn) {
              UploadData({OpenPump: isOn? '1':'0', o_i: '1'}, 'OpenPump')
            }
          })
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Divider()

      Text('定时灌溉')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('频率:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Row(){
          Radio({ value: '1', group: 'frequency' }).checked(true)
          Text('每天')}
        Row(){
          Radio({ value: '2', group: 'frequency' }).checked(false)
          Text('每三天')}
        Row(){
          Radio({ value: '3', group: 'frequency' }).checked(false)
          Text('每五天')}
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row(){
        Text('开始时间:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Row(){Text(`${this.selectTime.getHours()}:${this.selectTime.getMinutes()}`)}
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      .onClick(() => {
        TimePickerDialog.show({
          selected: this.selectTime,
          useMilitaryTime: true,
          onAccept: (value: TimePickerResult) => {
            this.selectTime.setHours(value.hour, value.minute)
            UploadData({
              StartHour:this.selectTime.getHours(),
              StartMinute:this.selectTime.getMinutes(),
              Interval: 600, //每隔多久浇一次水
              o_i: 1}, 'WaterPlan')
          }
        })
      })

      Row(){
        Text('持续时间:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text('10分钟')
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}

//通风界面
@Component
export struct VentilatePlanComponent {
  @State FanTemValue: number = 15
  @State SkyLightTemValue:number = 15
  @State inputValue: string = ''

  //设定风扇温度阈值的弹窗控制器
  FanTemController: CustomDialogController = new CustomDialogController({
    builder: OperationTextSetDialog({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $FanTemValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    customStyle: false
  })

  //设定天窗温度阈值的弹窗控制器
  SkyLightTemController: CustomDialogController = new CustomDialogController({
    builder: OperationTextSetDialog({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $SkyLightTemValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    customStyle: false
  })

  // 将dialogController置空
  aboutToDisappear() {this.FanTemController = null}

  onCancel() {console.info('Callback when the first button is clicked')}
  onAccept() {
    UploadData({
      FanTemperature:this.FanTemValue, WinTemperature:this.SkyLightTemValue}, 'VentilatePlan'
    )
    console.info('Callback when the second button is clicked')
  }
  exitApp() {console.info('Click the callback in the blank area')}

  //主构造体
  build() {
    Column({space:8}) {
      Text('手动通风')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('开启风扇:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})
          .onChange((isOn:boolean)=>{
            UploadData({Switch: isOn? 1:0}, 'OpenFan') //todo
          })

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Row(){
        Text('开启天窗:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})
          .onChange((isOn:boolean)=>{
            UploadData({Switch: isOn? 1:0}, 'OpenWin')

          })
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Divider()

      Text('自动通风')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('风扇阈值:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(String(this.FanTemValue))
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      .onClick(() => {
        this.FanTemController.open()})

      Row(){
        Text('天窗阈值:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(String(this.SkyLightTemValue))
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      .onClick(() => {
        this.SkyLightTemController.open()})
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}


//补光界面
@Component
export struct LightSubPlanComponent {
  @State LightSubValue: number = 15
  @State inputValue: number = 15

  //设定补光阈值的弹窗控制器
  FanTemController: CustomDialogController = new CustomDialogController({
    builder: OperationTextSetDialog({
      cancel: this.onCancel,
      confirm: this.onAccept,
      textValue: $LightSubValue,
      inputValue: $inputValue
    }),
    cancel: this.exitApp,
    autoCancel: true,
    alignment: DialogAlignment.Bottom,
    offset: { dx: 0, dy: -20 },
    gridCount: 4,
    customStyle: false
  })

  // 将dialogController置空
  aboutToDisappear() {this.FanTemController = null}

  onCancel() {console.info('Callback when the first button is clicked')}

  onAccept() {
    UploadData({
      Condition:this.LightSubValue}, 'LightSubPlan')
    console.info('Callback when the second button is clicked')
  }
  exitApp() {console.info('Click the callback in the blank area')}

  //主构造体
  build() {
    Column({space:8}) {
      Text('手动补光')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('开启补光系统:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})
          .onChange((isOn:boolean)=>{
            UploadData({Switch: isOn? 1:0}, 'OpenLightSub')
          })
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Divider().width('95%')
      Text('自动补光')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('补光阈值:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text(String(this.LightSubValue))
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      .onClick(() => {
        this.FanTemController.open()})
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}
