import axios from '@ohos/axios'
import router from '@ohos.router'

//标准弹窗模型
@CustomDialog
struct WrongRegisterDialog {
  Prompt:string
  controller: CustomDialogController
  build() {
    Column() {
      Text(this.Prompt)
        .fontSize(20)
        .margin({ top: 10, bottom: 10 })
    }
  }
}

@Component
export struct LRComponent{

  //数据变量
  @State username: string = ''
  @State password: string = ''
  @State commit: string = ''

  //控制变量
  @State LorR: boolean = true

  //构造注册错误弹窗
  WrongRegisterDialog: CustomDialogController = new CustomDialogController({
    builder: WrongRegisterDialog({Prompt:"两次输入密码不一致"})
  })

  //构造注册成功弹窗
  MadeRegisterDialog: CustomDialogController = new CustomDialogController({
    builder: WrongRegisterDialog({Prompt:"注册成功,请重新登录"})
  })

  //构造注册失败弹窗
  FailToRegisterDialog: CustomDialogController = new CustomDialogController({
    builder: WrongRegisterDialog({Prompt:"注册失败,用户已存在"})
  })

  //构造登录失败弹窗
  FailToLoginDialog: CustomDialogController = new CustomDialogController({
    builder: WrongRegisterDialog({Prompt:"登录失败,密码错误或用户不存在"})
  })


  build(){
    Column({space:'8'}){
      Column({space:10}){
        TextInput({placeholder:'用户名：'})
          .onChange((value) =>{
            this.username = value
          })
        TextInput({placeholder:'密码：'})
          .type(InputType.Password)
          .onChange((value) =>{
            this.password = value
          })
        if (!this.LorR){
          TextInput({placeholder:'确认密码：'})
            .type(InputType.Password)
            .onChange((value) =>{
              this.commit = value
            })
            .transition({ type: TransitionType.All, opacity: 0})
        }

        Button('登陆')
          .width('95%')
          .margin({top:10})
          .backgroundColor(this.LorR?Color.Blue:Color.Gray)
          .onClick(() =>{
            if (this.LorR){
              axios({//传递到服务器请求用户登录和相关数据
                method:"get",
                url:'http://localhost:8080/login',
                params:{
                  userName:this.username,
                  userPassword:this.password
                }
              }).then(res=>{
                if(res.data){
                  router.pushUrl({
                    url:'pages/LoadingPage',
                    //还需要式北来写全局变量更新：username,password
                    params:{
                      'userName': this.username,
                      'password': this.password
                    }
                  })
                }else{//登录失败 todo
                  this.FailToLoginDialog.open()
                }
              })
            }else {
              animateTo({
                duration: 650,
                curve: Curve.Smooth },
                () => {this.LorR = true})
            }
          })

        Button('注册') .width('95%')
          .backgroundColor(this.LorR?Color.Gray:Color.Blue)
          .margin({top:10})
          .onClick(()=>{
            if (!this.LorR){
              if (this.password == this.commit) {
                axios({//传递到服务器请求用户登录和相关数据
                  method:"get",
                  url:'localhost:8080/Register',
                  params:{
                    userName:this.username,
                    userPassword:this.password
                  }
                }).then(res=>{
                  if(res.data){
                    this.MadeRegisterDialog.open()
                  }else{//注册失败
                    this.FailToRegisterDialog.open()
                  }
                })
              }else {
                this.WrongRegisterDialog.open()
              }
            }else {
              animateTo({
                duration: 650,
                curve: Curve.Smooth },
                () => {this.LorR = false})
            }
          })
      }
      .backgroundImage($r('app.media.HalftoneGreen'))
      .borderRadius("10")
      .height('30%')
      .justifyContent(FlexAlign.SpaceEvenly)
    }
  }
}