import axios from '@ohos/axios';
import FarmBean from '../Common/Bean/Farmbean';
import UserInfoBean from '../Common/Bean/UserInfoBean';

//数字文本输入弹窗实体
@CustomDialog
export struct TextInputDialog {
  UserInfo: UserInfoBean = null;
  @State inputValue: number = 0;
  @State textValue: string = '';
  controllerTwo?: CustomDialogController
  // 若尝试在CustomDialog中传入多个其他的Controller，以实现在CustomDialog中打开另一个或另一些CustomDialog，那么此处需要将指向自己的controller放在所有controller的后面
  cancel: () => void = () => {}
  confirm: () => void = () => {}

  build() {
    Column() {
      Text('输入添加的农田ID').fontSize(20).margin({ bottom: 10 })
      TextInput({ placeholder: '', text: String(this.textValue) }).height(60).width('90%')
        .onChange((value: string) => {
          this.inputValue = Number(value)
        })
      Flex({ justifyContent: FlexAlign.SpaceAround }) {
        Button('取消')
          .onClick(() => {
            this.controllerTwo.close()
            this.cancel()
          }).backgroundColor(0xffffff).fontColor(Color.Black)
        Button('确定')
          .onClick(() => {
            axios({//确认以后上传农田ID,由服务器添加农田权限
              method:"get",
              url:'47.108.250.206:8080/AddFarm',
              params:{
                UserID: this.UserInfo.UserID,                 //用户ID
                FarmID: this.inputValue,        //将该用户希望添加的农田ID
              }
            }).then(res=>{
              if (res) {
                //添加成功 todo
              }else {
                //添加失败 todo
              }
            })
            this.confirm()
          })
          .backgroundColor(0xffffff).fontColor(Color.Red)
      }
      .margin({ bottom: 10 })
    }
    .borderRadius(10)
  }
}

//农田权限列表
@CustomDialog
export struct FarmShowDialog {
  UserInfo: UserInfoBean = null;
  FarmDetailShow: FarmBean[];

  cancel: () => void = () => {}
  confirm: () => void = () => {}

  TextInputDialog:CustomDialogController = new CustomDialogController({
    builder: TextInputDialog({UserInfo:this.UserInfo})
  })

  controller?: CustomDialogController

  build() {
    Column(){
      Row(){
        // Image($r('app.media.Refresh'))
        // .autoResize(true)
        Text()
          .onClick(()=>{
            axios({//传递到服务器请求用户登录和相关数据
              method:"get",
              url:'47.108.250.206:8080/GetUserData',
              params:{
                userName:this.UserInfo.Username
              }
            }).then(res=>{
              this.UserInfo = new UserInfoBean(this.UserInfo.Username, res.data.userID, res.data.List)
            })
          })
        Text('我管理的农田')
          .fontSize(20)

        Button('+')
          .onClick(()=>{
            this.TextInputDialog.open()
          })
      }

      List({space: 8}) {
        ForEach(this.FarmDetailShow, (Farm:FarmBean, index:number) => {
          //FarmShow不能删除,删除会不能预览
          ListItem() {
            Row(){
              Text(`${Farm.name}  ${Farm.fieldID}`)
                .fontSize(22)

            }
          }
          .onClick(()=>{})
        })
      }
      .height('100%')
      .listDirection(Axis.Vertical) //列表垂直方向布局
    }
  }
}